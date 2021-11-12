import re
import math


class Tag:
    def __init__(self, corpus):
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
        self.__stat_word()

    # 统计（词语-词频-词性），词性转移矩阵，词性频率表，并持久化存储
    def __stat_word(self):
        # 统计词语-词频，词性
        word_dic = {}
        for sentence in self.corpus:
            for item in sentence:
                pos = item.find('/')
                word = item[:pos]
                part = item[pos + 1:]
                if word not in word_dic.keys():
                    # 采用两层字典的结构来保存词语-词性-词频
                    word_dic[word] = {
                        part: 1
                    }
                else:  # 词语已经存在，此时判断词性
                    if part not in word_dic[word].keys():
                        word_dic[word][part] = 1
                    else:
                        word_dic[word][part] += 1
        self.word_dic = word_dic

        # 统计词性频率表
        part_dic = {}
        for word in word_dic.keys():
            for part in word_dic[word].keys():
                if part not in part_dic.keys():
                    part_dic[part] = 1
                else:
                    part_dic[part] += 1
        self.part_dic = part_dic

        # 统计词性转移矩阵
        p2p_dic = {}
        # 只留下标签
        corpus = []
        for sentence in self.corpus:
            handled_sentence = []
            for item in sentence:
                handled_sentence.append(item[item.find('/') + 1:])
            corpus.append(handled_sentence)
        # 用dic保存该矩阵
        for sentence in corpus:
            for index in range(0, len(sentence) - 2):  # 最后一位\n不考虑
                first_part = sentence[index]
                second_part = sentence[index + 1]
                if first_part not in p2p_dic.keys():
                    p2p_dic[first_part] = {
                        second_part: 1
                    }
                else:
                    if second_part not in p2p_dic[first_part].keys():
                        p2p_dic[first_part][second_part] = 1
                    else:
                        p2p_dic[first_part][second_part] += 1
        # 将矩阵的所有项补齐
        for p1 in p2p_dic.keys():
            for p2 in p2p_dic[p1].keys():
                if p1 not in p2p_dic[p2].keys():
                    p2p_dic[p2][p1] = 0
        # 持久化存储
        self.p2p_dic = p2p_dic

        # 保存首词性的出现概率
        p1_dic = {}
        for sentence in corpus:
            p1 = sentence[0]
            if p1 not in p1_dic.keys():
                p1_dic[p1] = 1
            else:
                p1_dic[p1] += 1
        for key in p1_dic.keys():
            p1_dic[key] /= float(len(corpus))
        # 持久化存储
        self.p1_dic = p1_dic

    def tag(self, sentence):
        p2p_dic = self.p2p_dic  # 词性转移矩阵
        p1_dic = self.p1_dic  # 首词性概率矩阵
        part_dic = self.part_dic  # 词性频度向量
        word_dic = self.word_dic  # （词语 - 词频 - 词性）

        extra_info = [{} for i in range(len(sentence))]
        # extra_info[0]={
        #     'type':(float(posibility),str(father_type))
        # }

        # 初始化第一个词的伴随信息
        first_word = sentence[0]
        for part in word_dic[first_word].keys():
            extra_info[0][part][0] = math.log2(p1_dic[part])
            extra_info[0][part][1] = 'start'
        # 初始化后面词的伴随信息
        for index in range(1, len(sentence)):
            for part in word_dic[sentence[index]].keys():
                extra_info[index][part][0] = 0.0
                extra_info[index][part][1] = ''

        for index in range(0, len(sentence) - 1):
            From = sentence[index]
            To = sentence[index + 1]
            for fromtype in word_dic[From].keys():
                for totype in word_dic[To].keys():
                    # 计算转移概率以及发射概率
                    p = math.log2(p2p_dic[fromtype][totype] / part_dic[fromtype]) \
                        + math.log2(word_dic[To][totype] / part_dic[totype])
                    # 若出边节点的对应词性的代价较高则更新
                    if extra_info[index + 1][totype][0] < p:
                        extra_info[index + 1][totype][0] = p
                        extra_info[index + 1][totype][1] = fromtype

        # 找到最大值并回溯节点
        final_type = ''
        final_pos = 0
        for type in extra_info[-1].keys():
            if (extra_info[-1][type][0] > final_pos):
                final_pos = extra_info[-1][type][0]
                final_type = type
        path = []
        current_type = final_type
        for info in extra_info.reverse():
            path.insert(0, info[current_type][1])
            current_type = info[current_type][1]
        return path

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
                test_corpus.append(line.split(' '))

        # 进行正确率的计算
        total_word = 0
        correct_word = 0
        for sentence in test_corpus:
            sentence_without_type = []
            for item in sentence:
                sentence_without_type.append(item[:item.find('/')])
            result = self.tag(sentence_without_type)
            jiaoji = set(result) & set(sentence_without_type)
            total_word += len(sentence_without_type)
            correct_word += len(jiaoji)

        print('accuracy:{}'.format(correct_word / total_word))
