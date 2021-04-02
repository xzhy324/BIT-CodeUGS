#include "IntChar.h"
int main(){
    IntChar IC("ABCD");
	IC.INT();           // 输出该字符串对应的整数
	IC.Binary();  // 输出该字符串的二进制形式
	cout << endl << IC.At(3) << endl;  // 输出第三个字符：C
    IntChar IC1("ABC");
	IC1.INT();           // 输出该字符串对应的整数
	IC1.Binary();  // 输出该字符串的二进制形式
	cout << endl << IC1.At(3) << endl;
    IC.PrintString(1094861636);
}