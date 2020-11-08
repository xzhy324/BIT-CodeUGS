package basicGrammer;

public class UseOperator {
    public static void main(String[] args) {

        int a = 1, b = 2, c = 3;
        //计算平均值，应该采用浮点数除法，
        //否则，分子分母都是整数，就变成整除了
        double average = (a + b + c) / (double) 3;
        System.out.println(average); //2.0

        System.out.println();

        //复合赋值运算符示例（注意前一句执行的结果会影响到后一句）
        System.out.println(a += 1);  //2
        System.out.println(a -= 1);  //1
        System.out.println(a *= 2);  //2
        System.out.println(a /= b);  //1
        System.out.println(b % 3);   //2

        System.out.println();

        //逻辑关系运算符
        int m = 1, n = 2;
        System.out.println(m == n); //false
        System.out.println(m != n); //true
        System.out.println(m > n);  //false
        System.out.println(m > n && m < 100); //false
        System.out.println(m > n || m < 100); //true
        System.out.println(!(m > n));  //true

        System.out.println();

        //位操作运算符
        System.out.println(1 & 0); //0
        System.out.println(1 | 0);   //1
        System.out.println(1 ^ 0); //1
        System.out.println(~0);    //-1
        System.out.println(1 << 2);  //4

        System.out.println();

        int x, y, z = 3;
        //实际开发中，别写这种奇葩的代码！
        System.out.println(x = y = z); //3
    }
}
