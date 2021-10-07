"""
@2021.10.7
@xzy
"""
import this

# 大小写转换
name = "dAniel xu"
print(name.title())  # 首字母大写，其余小写
print(name.upper())  # 全部大写
print(name.lower())  # 全部小写

# 前置f格式字符串
string = 'loves'
print(f"xzy {string} lmy!")
# 后置f格式字符串
print("lmy {} xzy!".format("loves"))

# 删除空白
string = ' 123 '
string.strip()
string.lstrip()
string.rstrip()

# python的字符串处理十分强大

# 乘方
print(10**6)
print(1.2**3.2)

# 注意浮点数的运算误差
print(0.2+0.1)

# 任意两数相除一定是浮点数
print(4/2)

print(4//2)

# 同时给多个变量赋值,一一对应关系
x, y, z = 0, 0, 0
# python没有常量类型，一般全大写以表示常量
CONS_DATA = 0x3f3f3f
