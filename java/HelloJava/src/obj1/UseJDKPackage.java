package obj1;

//����JDK�����ð��е���

import javax.swing.*;
import java.util.Date;

public class UseJDKPackage {

    public static void main(String[] args) {
        //����javax.swing���е�JOptionPane�ľ�̬����
        JOptionPane.showMessageDialog(null, "����һ����Ϣ��");

        //����һ��java.util���е�Date()���󣬻�ȡ��ǰʱ��
        String now = new Date().toString();
        System.out.println("��ǰʱ��Ϊ��" + now);

    }

}


