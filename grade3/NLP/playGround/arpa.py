import arpa
from arpa import *

import jieba

cut_result = jieba.lcut('只是在牧师协会眼中，这是神灵赐予他们的礼物。')
cut_result.replace('牧师','<unk>')
cut_result[cut_result.index('牧师')] = '<unk>'