package obj1;

public class ClassAndObjectTest {

    public static void main(String[] args) {
        //�������ʵ��������һ���������������һʵ��
        MyClass obj = new MyClass();
        //ͨ���������������Ĺ��з���
        obj.myMethod("Hello");
        //�����Ը�ֵ
        obj.setValue(100);
        //������Եĵ�ǰֵ
        System.out.println(obj.getValue());
        //ֱ�ӷ��ʶ������ֶ�
        obj.Information = "Information";
        //����������ֶεĵ�ǰֵ
        System.out.println(obj.Information);
    }
}

/**
 * �Զ���Java���ʾ��
 */
class MyClass {
    // �����ֶ�
    public String Information = "";
    // �������ԣ�˽���ֶ�+get����+set����
    private int value;

    // �Զ��幫��Javaʵ������
    public void myMethod(String argu) {
        System.out.println(argu);
    }

    public int getValue() {
        return value;
    }

    public void setValue(int value) {
        this.value = value;
    }

}
