package basicGrammer;

import java.util.Date;

public class UseVar {
    public static void main(String[] args) {

        //使用var定义局部变量，是JDK10引入的特性
        //变量的类型，由Java编译器依据其接收的值自动判断
        //在本例中，intValue的类型为int。
        var intValue = 100;
        //以下语句将intValue变量加一，相当于
        //intValue=intValue+1
        intValue++;
        int newValue = 101;
        //输出：true
        System.out.println(intValue == newValue);

        //var所定义的变量，其类型不受限制
        var info = "当前时间为：";
        var now = new Date();
        //var所定义的变量，其用法与普通变量没什么两样
        //当前时间为：Wed Sep 23 09:02:24 CST 2020
        System.out.println(info + now.toString());
        //以下两句调用JDK所提供之“反射“功能，提取特定变量的类型信息
        //java.lang.String
        System.out.println(info.getClass().getName());
        //java.util.Date
        System.out.println(now.getClass().getName());

    }
}
