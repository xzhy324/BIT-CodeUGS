"""
@2021.10.7
@xzy
"""
myList = ['cake', 'apple', 'banana']
print(myList[-1])  # 访问最后一个元素

# 元素的插入
# way 1：
myList.append('orange')
# way 2:(插入点之后的元素右移)
myList.insert(1, 'pie')
print(myList)

# 元素的删除
# way1:
tmp = myList.pop()  # pop有返回值
tmp = myList.pop(2)  # 可以指定删除位置
# way2:
del myList[-1]  # del没有返回值
# way3:
myList.remove('apple')  # 根据值删除，注意只删除第一个匹配到的值

# 列表排序
# sort()永久排序
myList.sort()  # ascend
myList.sort(reverse=True)
# sorted()临时排序
print(sorted(myList, reverse=True)[0])  # 返回值也是一个list

#