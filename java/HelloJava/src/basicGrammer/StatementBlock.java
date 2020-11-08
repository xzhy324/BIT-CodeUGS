package basicGrammer;

public class StatementBlock {

    static {
        System.out.println("类初始化语句块");
    }
    //方法（或函数）的语句块
    public static void main(String[] args) {
        //for和if语句的语句块
        for (int i = 0; i < 5; i++) {
            if (i != 4) {
                System.out.println(i + ",");
            } else {
                System.out.println(i);
            }
        }
        VariableScopeInBlock();
    }

    //语句块中变量的作用域
    private static void VariableScopeInBlock() {
        int i = 1;
        //定义一个语句块
        {
            //语句块内定义的j和sum,只能在本语句块内所使用
            int j = 2;
            //在本语句块中，可以使用外部定义的变量i
            int sum = i + j;
            System.out.println(sum);//3
        }
        //在语句块外部，不能再访问变量j和sum
        //System.out.println(j);
    }
}
