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
    //下面这句在初始化块之前与之后，会影响到field字段的初始值
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
