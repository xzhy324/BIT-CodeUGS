i = 0
numbers = []

while i < 6:
	print(f"At the top i is {i}")
	numbers.append(i)#将参数加入到列表numbers中

	i += 1
	print("Numbers now: ", numbers)#表示现在numbers中的参数
	print(f"At the bottom i is {i}")#表示此时要放进列表中的数

print("The numbers: ")

for num in numbers:
	print(num,end='')#end=''可以去掉换行符
