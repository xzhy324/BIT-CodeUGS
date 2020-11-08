package basicGrammer;

public class ConstantAndVariable {

    //常量定义
    public static final int MAX_NUMBER = 255;

    public static void main(String[] args) {
        //变量定义
        int num = 100;
        //将变量num的值取出来，加1，再保存回变量num中
        num=num+1;
        num+=1;
        //变量和常量之间可以进行运算
        int num2=num;

        System.out.println(num + MAX_NUMBER);//356
    }
}
