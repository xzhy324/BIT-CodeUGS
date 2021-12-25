from __future__ import print_function
import json
import re
import six
import paddlehub as hub
import matplotlib.pyplot as plt
import seaborn as sns
import numpy as np
import pandas as pd

if __name__ == "__main__":
    # 加载senta模型
    senta = hub.Module(name="senta_bilstm")
    for sheet_num in range(0,3):
        test_text = []
        # 把要测试的短文本以str格式放到这个列表里
        df = pd.DataFrame(pd.read_excel("./Corpus/data1.xlsx", engine='openpyxl', sheet_name=sheet_num))
        for list_item in df.values:
            test_text.append(list_item[0])

        # 指定模型输入
        input_dict = {"text": test_text}

        # 把数据喂给senta模型的文本分类函数
        results = senta.sentiment_classify(data=input_dict)
        draw_data = []  # 将正向得分画成一张图
        avg_score = 0.0  # 平均得分
        # 遍历分析每个短文本
        for index, text in enumerate(test_text):
            results[index]["text"] = text
        for index, result in enumerate(results):
            draw_data.append(float(results[index]['positive_probs']))
            avg_score += float(results[index]['positive_probs'])
            if six.PY2:
                print(json.dumps(results[index], encoding="utf8", ensure_ascii=False))
            else:
                print('index: {},\t predict: {},\t  positive_prob: {}'.format(index + 1,
                                                                              results[index]['sentiment_key'],
                                                                              results[index]['positive_probs']))
        avg_score /= len(df.values)

        #  Cut the window in 2 parts 将窗口分为两部分
        #  sharex共享x轴，图像分为上下两部分，上面部分ax_box占比0.15，下面部分ax_hist占比0.85
        f, (ax_box, ax_hist) = plt.subplots(2, sharex='all', gridspec_kw={"height_ratios": (.15, .85)})
        plt.xlim(0, 1)
        #  Add a graph in each part 绘制两种不同的图像
        sns.boxplot(draw_data, ax=ax_box)
        sns.distplot(draw_data, ax=ax_hist, bins=10)

        #  Remove x axis name for the boxplot 不显示箱形图的横坐标
        ax_box.set(xlabel='')
        plt.show()

        # x = [i+1 for i in range(0,len(df.values))]
        # plt.plot(x,draw_data)
        # plt.show()

        print(f"avg positive_probs is :{avg_score}")
        print()
