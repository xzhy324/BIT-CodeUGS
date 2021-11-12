from partition import Partition
from tag import Tag

if __name__ == '__main__':
    p1 = Partition(
        corpus='./dataset/mini.txt',
    )
    p2 = Partition(
        trainNow=False,
        model_1gram_path='./model/2014_corpus_train.1gram',
        model_2gram_path='./model/2014_corpus_train.2gram'
    )
    p2.evaluate('./dataset/2014_corpus_test1.txt')

    t1 = Tag(corpus='./dataset/2014_corpus_train.txt')
    t1.tag(p2.segment("今天是个好日子。"))
    t1.evaluate(testset_path='./dataset/2014_corpus_test.txt')
