package obj1;

public class InitializeBlockDemo {

    /**
     * @param args
     */
    public static void main(String[] args) {

        InitializeBlockClass obj = new InitializeBlockClass();
        System.out.println(obj.field);

        obj = new InitializeBlockClass(300);
        System.out.println(obj.field);
    }

}

class InitializeBlockClass {
    //��������ڳ�ʼ����֮ǰ��֮�󣬻�Ӱ�쵽field�ֶεĳ�ʼֵ
    //public int field=100;

    public int field = 100;

    {
        field = 200;
    }

    public InitializeBlockClass(int value) {
        this.field = value;
    }

    public InitializeBlockClass() {

    }
}
