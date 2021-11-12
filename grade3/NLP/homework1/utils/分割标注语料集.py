count = 0
f = open('../dataset/2014_corpus.txt', encoding='utf8')
for line in f.readlines():
    count += 1
pos = int(count * 0.9999)
f.close()

f = open('../dataset/2014_corpus.txt', encoding='utf8')
with open('../dataset/2014_corpus_train1.txt', encoding='utf8', mode='w') as a:
    for i in range(0,pos):
        a.write(f.readline())
with open('../dataset/2014_corpus_test1.txt', encoding='utf8', mode='w') as a:
    for i in range(pos,count):
        a.write(f.readline())