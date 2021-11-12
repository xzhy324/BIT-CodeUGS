import re
import math


class Partition:

    def __init__(self, corpus='', trainNow=True, model_1gram_path='', model_2gram_path=''):
        """
        if trainNow=True，需指定语料库路径
        elif trainNow=False，需指定n元语法模型路径
        使用语料库文件训练模型

        :param trainNow:语料训练模式/直调模型模式
        :param corpus: 语料库文件路径
        :param model_1gram_path 1元语法模型路径
        :param model_2gram_path 2元语法模型路径
        """
        self.model_1gram_path = model_1gram_path
        self.model_2gram_path = model_2gram_path
        if trainNow:
            print('training!')
            self.fileName = corpus[corpus.rfind('/') + 1:  corpus.rfind('.')]
            self.corpus = []
            """
            初始化语料
            返回结果形如：[sentence1,sentence2,...]
                        sentence = ['word1/n,word2/v',...]
            """
            with open(corpus, encoding='utf-8') as f:
                content = f.readlines()
                for line in content:
                    res_lists = re.findall(r"(\[.*?\])", line)  # 先处理中括号,返回一个list，里面是【.. ..】串
                    for res in res_lists:
                        unhandled_word = res[1:-2]
                        insert_flag = True
                        handled_word = ''
                        for i in range(0, len(unhandled_word)):
                            if unhandled_word[i] == '/':
                                insert_flag = False
                            elif unhandled_word[i] == ' ':
                                insert_flag = True
                            else:
                                if insert_flag:
                                    handled_word += unhandled_word[i]
                        line = line.replace(res, handled_word)  # 一次替换一个部分
                    self.corpus.append(line.split(' '))  # 将处理好的结果添加进corpus中
            self.__stat_ngram()  # 统计并保存用于分词的一元和二元语法，并持久化存储
            print('done!')

    # 统计一元和二元语法，并持久化存储
    def __stat_ngram(self):
        # ngram用于分词，此时不需要词性信息，故首先对corpus进行加工，删去词性，并在句子的首尾增加特定的标志
        corpus = []
        for sentence in self.corpus:
            handled_sentence = ['始##始', ]
            for word in sentence:
                handled_sentence.append(word[0:word.find('/')])
            handled_sentence.append('末##末')
            corpus.append(handled_sentence)

        # 训练一元语法
        dic_1gram = {}
        for sentence in corpus:
            for word in sentence:
                if word in dic_1gram.keys():
                    dic_1gram[word] += 1
                else:
                    dic_1gram[word] = 1

        # 保存一元语法结果
        """
        保存格式为： 词语 频次  (占据一行)
        """
        with open("./model/" + self.fileName + '.1gram', encoding='utf-8', mode='w') as f:
            for word in dic_1gram.keys():
                f.write(word + ' ' + str(dic_1gram[word]) + '\n')

        # 训练二元语法
        dic_2gram = {}
        for sentence in corpus:
            for index in range(0, len(sentence) - 1):
                wordPair = sentence[index] + ' ' + sentence[index + 1]
                if wordPair in dic_2gram.keys():
                    dic_2gram[wordPair] += 1
                else:
                    dic_2gram[wordPair] = 1

        # 保存二元语法结果
        """
        保存格式为： 词语 词语 频次 (占据一行)
        """
        with open("./model/" + self.fileName + '.2gram', encoding='utf-8', mode='w') as f:
            for wordPair in dic_2gram.keys():
                f.write(wordPair + ' ' + str(dic_2gram[wordPair]) + '\n')

        # 修改为当前模型路径
        self.model_1gram_path = "./model/" + self.fileName + '.1gram'
        self.model_2gram_path = "./model/" + self.fileName + '.2gram'

    # 词网构造函数
    def __generate_wordnet(self, sentence, model_path=''):
        """
        根据输入的句子以及一元语法模型产生词网，词网保证是联通的
        :param model_path:
        :param sentence: 待构建词网的句子
        :return: 词网[['w1','w2',...],[],...] , 一元模型字典
        """
        slen = len(sentence)
        if model_path == '':
            model_path = self.model_1gram_path

        # 根据文件路径加载一元语法的统计信息，保存在model_dic中
        model_dic = {}
        with open(model_path, encoding='utf-8') as f:
            lines = f.readlines()
            for line in lines:
                space_pos = line.find(' ')
                word = line[:space_pos]
                frequency = int(line[space_pos + 1:])
                model_dic[word] = frequency

        # 根据句子来构建单字开头的所有可能值，使用list[list[]]来构造每个字开头的词，size=len(sentence)+2,每层的初值设为[]
        """
        词网layers结构为[[word1,word2],[],...]  第i层对应第i-1个字符（句子正文从1开始，到len(sentence)）
        """
        layers = []
        # 初始化
        for index in range(0, slen + 2):
            layers.append([])
        layers[0].append('始##始')  # 这样第0层元素个数为1
        layers[-1].append('末##末')

        # 取所有的子区间[i,j],判断是否在1gram字典当中
        for i in range(1, len(layers) - 1):
            for j in range(i, len(layers) - 1):
                if sentence[i - 1:j] in model_dic.keys():
                    layers[i].append(sentence[i - 1:j])

        # 刷一遍图保证连通性,处理空白行
        i = 0
        while i < len(layers):
            if len(layers[i]) == 0:  # 若当前行的出边为0
                j = 0  # 初始化j
                for j in range(i + 1, len(layers) - 1):  # 寻找首非空行
                    if len(layers[j]):
                        break
                layers[i].append(sentence[i - 1:j - 1])  # 将[i,j)确定的未识别词填入词网
                i = j
            else:  # 当前行存在出边
                i += len(layers[i][0]) if i != 0 else 1  # 注意第一个元素是最短的词语，下一位置从该词开始更新即可
        return layers, model_dic

    # 根据n元语法模型对句子进行分词
    def segment(self, sentence, model_1gram_path='', model_2gram_path='', a=0.90, b=0.90):
        """
        一元语法模型可缺省，默认加载训练模型时的一元语法统计模型
        :param sentence: 待分词的句子
        :param model_1gram_path: 一元模型路径
        :param model_2gram_path: 二元模型路径
        :return: 分好词的句子，以list形式呈现
        :param a: MLE平滑因子1
        :param b: MLE平滑因子2
        """

        # 加载词网，加载一元模型词典
        wordnet, model_1gram_dic = self.__generate_wordnet(
            sentence=sentence,
            model_path=model_1gram_path
        )
        N_corpus = 0
        for key in model_1gram_dic.keys():
            N_corpus += model_1gram_dic[key]

        # 加载二元模型词典
        if model_2gram_path == '':
            model_2gram_path = self.model_2gram_path
        model_2gram_dic = {}
        with open(model_2gram_path, encoding='utf-8') as f:
            lines = f.readlines()
            for line in lines:
                space_pos = line.rfind(' ')
                wordPair = line[:space_pos]
                frequency = int(line[space_pos + 1:])
                model_2gram_dic[wordPair] = frequency

        # 通过词网构造一个辅助的结构，与生成词网的结构完全一致,用于记录点的前驱点和最小转移花费
        extra_info = [[] for i in range(len(wordnet))]
        for i in range(1, len(wordnet)):
            for word in wordnet[i]:
                dic = {
                    'from': (-1, -1),
                    'cost': float("inf")
                }
                extra_info[i].append(dic)
        # 特别注意开始标志的值需置为0，表示取对数前以概率1进行转移
        start_dic = {
            'cost': 0.0,
            'from': (-1, -1)
        }
        extra_info[0].append(start_dic)

        # viterbi算法
        for i in range(0, len(wordnet) - 1):
            if len(wordnet[i]) == 0:  # 词网一定联通，因此光标移动到未加入词时一直往下找到第一个可作为起点的词即可
                continue
            for j in range(0, len(wordnet[i])):
                current_word = wordnet[i][j]
                next_i = i + len(current_word)  # 更新的是下一个词的概率
                if (i, j) == (0, 0):
                    next_i = 1
                k = 0  # 记录当前的next_word的下标
                for next_word in wordnet[next_i]:
                    # 计算极大似然概率
                    wordPair = current_word + ' ' + next_word
                    c_2gram = 0 if wordPair not in model_2gram_dic.keys() else model_2gram_dic[wordPair]
                    c_1gram = 1 if current_word not in model_1gram_dic.keys() else model_1gram_dic[current_word]
                    # MLE平滑策略
                    p = a * (b * c_2gram / c_1gram + 1 - b) + (1 - a) * (c_1gram + 1) / N_corpus
                    cost = -math.log(p) + extra_info[i][j]['cost']
                    if cost < extra_info[next_i][k]['cost']:
                        extra_info[next_i][k]['cost'] = cost
                        extra_info[next_i][k]['from'] = (i, j)

                    k += 1

        # 还原viterbi算法结果
        path = []
        father = extra_info[-1][0]['from']
        while father != (-1, -1):
            path.insert(0, father)
            father = extra_info[father[0]][father[1]]['from']
        path.remove((0, 0))  # 删除起始标记
        return [wordnet[t[0]][t[1]] for t in path]

    # 测试模型效果
    def evaluate(self, testset_path):
        # 去除词性标签
        test_corpus = []
        with open(testset_path, encoding='utf8') as f:
            for line in f.readlines():
                res_lists = re.findall(r"(\[.*?\])", line)  # 先处理中括号,返回一个list，里面是【.. ..】串
                for res in res_lists:
                    unhandled_word = res[1:-2]
                    insert_flag = True
                    handled_word = ''
                    for i in range(0, len(unhandled_word)):
                        if unhandled_word[i] == '/':
                            insert_flag = False
                        elif unhandled_word[i] == ' ':
                            insert_flag = True
                        else:
                            if insert_flag:
                                handled_word += unhandled_word[i]
                    line = line.replace(res, handled_word)  # 一次替换一个部分
                line = line.split(' ')
                newline = []
                for item in line:
                    newline.append(item[:item.find('/')])
                test_corpus.append(newline)
        # 计算P R F1 需要统计的值
        A = 0
        B = 0
        AandB = 0
        for correct_answer in test_corpus:
            test_string = ''
            for word in correct_answer:
                test_string += word
            test_answer = self.segment(test_string)
            jiaoji = set(correct_answer) & set(test_answer)

            A += len(correct_answer)
            B += len(test_answer)
            AandB += len(jiaoji)

        P = AandB / float(A)
        R = AandB / float(B)
        F1 = 2 * R * P / (R + P)
        print("P:{},R:{},F1:{}".format(P, R, F1))
