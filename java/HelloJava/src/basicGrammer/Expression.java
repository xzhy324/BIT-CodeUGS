package basicGrammer;

public class Expression {
    public static void main(String[] args) {

        int a = 100;
        int b = 10;
        //表达式肯定有一个值，这个值可以被另一个变量所接收
        int result = a / b - 5;
        System.out.println(result); //5
        //可以把表达式当成一个值，传给另外一个函数作为参数
        System.out.println(++a); //101

        CaculateRoot();
    }

    //计算一元二次方程的根
    private static void CaculateRoot() {
        double a = 5;
        double b = -4;
        double c = -1;
        //依据求根公式，开始构建表达式
        double delta = b * b - 4 * a * c;
        if (delta < 0) {
            System.out.println("此方程无解");
            return;
        }
        double x1 = (-b + Math.sqrt(delta)) / (2 * a);
        double x2 = (-b - Math.sqrt(delta)) / (2 * a);
        System.out.println("x1=" + x1); //x1=1.0
        System.out.println("x2=" + x2); //x2=-0.2
    }
}
