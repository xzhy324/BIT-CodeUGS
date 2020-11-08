package obj1;

//导入JDK中内置包中的类

import javax.swing.*;
import java.util.Date;

public class UseJDKPackage {

    public static void main(String[] args) {
        //调用javax.swing包中的JOptionPane的静态方法
        JOptionPane.showMessageDialog(null, "这是一个消息框");

        //创建一个java.util包中的Date()对象，获取当前时间
        String now = new Date().toString();
        System.out.println("当前时间为：" + now);

    }

}


