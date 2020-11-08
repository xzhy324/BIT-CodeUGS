
print("hello world!")
print("i don't want to start a new line!",end="")#,end=""可以不换行,当然引号内也可以填充
print("Alright.")
print("3+2<5-7 is it ture?",3+2<5-7,'aha, u r clever')
print('------------------------------')

my_name = 'Daniel'
print(f"let's talk about {my_name}")
print(f"what's 3+2? {3+2}")
#用{}来把变量框起来，而f的作用是使得{}在“”内会被侦测到,{}内可以是表达式或者变量
info = f'My name is {my_name}!'#注意该例中f{}的用法
print(info,'what about u?')
print('------------------------------')

hilarous = False
joke_evaluation = "Isn't that joke sound funny? {}"
print(joke_evaluation.format(hilarous))
print('------------------------------')

w = 'thats a ...'
e = 'complete string!'
print(w*3,'\n','.'*10)
print(w+e)#字符串支持直接倍乘和首位衔接
print('------------------------------')

formatter = '{}\\{}\\{}\\{}'
print(formatter.format(1,2,
                       "three",3-2<5-7,) * 2)
#注意print可以分行且format内的数据类型可以不用预先说明
print('------------------------------')

print('''这样打印出来的字符串就是每行自带回车的,
因为在输入文本的时候我们键入了回车换行符.
同时，在字符串中，反斜杠n是可以被读取的
我要从这里\n断开这句话
''')
print('------------------------------')


age = input("how old r u? ")
print("and your weight?",end=" ")
weight = input()
print(f"so your age is {age}!", f"your weight is ",weight)
print('------------------------------')
