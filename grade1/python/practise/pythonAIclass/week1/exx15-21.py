
#from sys import argv
#script,use_name = argv
#prompt ='>'
#print(f"Hi {use_name}, i'm the {script} script.")
#print("i'd like to ask you some questions.")
#print(f"do you like me {use_name}?")
#likes = input(prompt)
#print(f"where do you live {use_name}?")
#lives = input (prompt)
#print("what kind of computer do you have?")
#computer = input(prompt)
#print(f"""alright, so you said {likes} about me.
#you live in {lives}. not sure where that is.
#and you have a {computer} computer. niece.""")
#--------------------------------------------------------------------------------------------

#from sys import argv
#script,filename = argv
#print(f"here is your file {filename}:")
#print(txt.read())

#print("type the filename again:")
#file_again = input(">")
#txt_again = open(file_again)
#print(txt_again.read())
#-----------------------------------------------------------------------------------
#from sys import argv
#script, filename = argv
#print(f"we are going to erase{filename}")
#print("if you don't want that, hit CTRL-C(^C).")
#print("if you want that, hit RETURN.")
#input("?")
#print("opening the file...")
#target=open(filename,'w','r')

#print("Truncating the file. goodbye!")
#target.truncate()#清空
#print("now, i'm going to ask you for three lines.")
#line1 = input("line1:")
#line2 = input("line2:")
#line3 = input("line3:")
#print("i am going to write these to the file.")
#target.write(line1)
#target.write("\n")
#target.write(line2)
#target.write("\n")
#target.write(line3)
#target.write("\n")
#print("and finally, we close it.")
#target.close()
#--------------------------------------------------------------------------------------------------
#from sys import argv
#from os.path import exists
#import codecs
#script,from_file,to_file = argv
#print(f"copying from {from_file} to {to_file}")
#可以将这在一行代码中执行
#in_file = codecs.open(from_file,encoding='utf-8')#打开文件
#indate = in_file.read()#读取文件
#print(f"the input file is {len(indate)} bytes long")#计算文件大小
#print(f"does the output file exist? {exists(to_file)}")#判断要写入的文件是否存在
#print("read, hit return to continue, stop to abort.")
#input(">")
#out_file = codecs.open(to_file,'w',encoding='utf-8')
#out_file.write(in_file.read())
#print("alright, all done.")
#out_file.close()
#in_file.close()
#----------------------------------------------------------------------------------------------------

#def print_two(*args):
#    arg1,arg2,arg3 = args#arg1,arg2,等都是定义的参数个数
#    print(f"arg1: {arg1}, arg2: {arg2}, arg3: {arg3}")

#def print_two_again(arg1,arg2):
    #arg4,arg5 = args
#    print(f"arg3: {arg1}, arg2: {arg2}")

#def print_one(arg1):#接受单个参数
#    print(f"arg1: {arg1}")

#def print_none():#不接受如何参数
#    print(f"i got nothing.")

#print_two('zed','shaw','chen')#将参数"zed","shaw"，'chen'传入
#print_two_again("zeda","shawa")
#print_one("first!")
#print_none()


#def cheese_and_crackers(cheese_count,boxes_of_crackers):
#    print(f"you have {cheese_count} cheeses!")
#    print(f"you have {boxes_of_crackers} boxes of crackers!")
#    print("man that's enough for a party!")
#    print("get a blanket.\n")
#    print("we can just give the function numbers directly:")
#cheese_and_crackers(20,30)


#print("or, we can use variables from our script:")#将另外的变量给上面的两个变量
#amount_of_cheese = 10
#amount_of_crackers = 50
#cheese_and_crackers(amount_of_cheese,amount_of_crackers)

#print("we can even do math inside too:")
#cheese_and_crackers(10+20,5+6)#加法执行后，再将值赋给对应的变量
#-------------------------------------------------------------------------------------------------------
#from sys import argv
#script ,input_file = argv
#def print_all(f):
#    print(f.read())
#def rewind(f):
#    f.seek(0)
#def print_a_line(line_count,f):
#    print(line_count,f.readline())
#current_file = open(input_file)
#print("first let's print the whole file:\n")
#print_all(current_file)
#print("now let's rewind, kind of like a tape.")
#rewind(current_file)

#print("let's print three lines:")

#current_line = 1
#print_a_line(current_line,current_file)

#courrent_line = current_line+1
#print_a_line(current_line,current_file)

#current_line = current_line+1

#print_a_line(current_line,current_file)
#-------------------------------------------------------------------------------------------------------
def add(a,b):
    print(f"adding {a} + {b}")
    return a+b

def subt(a,b):
    print(f"subt {a} - {b}")
    return a-b

def mult(a,b):
    print(f"mult {a} * {b}")
    return a*b


print("lets do some math with just fuction")
age=add(30,5)
height=subt(56,6)
weight=mult(24,234)
print(f"age: {age}, height: {height}, weight: {weight}")

print("here is a puzzle")
whe = add(age,subt(height,mult(weight,5)))
print(f"that becomes: " ,{whe} ,"can you do it hand?")
