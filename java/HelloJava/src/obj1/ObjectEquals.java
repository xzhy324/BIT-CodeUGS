package obj1;

public class ObjectEquals {


    public static void main(String[] args) {
        MyTestClass obj1 = new MyTestClass(100);
        MyTestClass obj2 = new MyTestClass(100);
        System.out.println(obj1 == obj2);
        System.out.println(obj1.equals(obj2));
    }

}

class MyTestClass {
    public int Value;
    //ע�⣺ֻ�в�������ΪObject�ģ�������д��Object��equals����
    //��������ΪMyTestClass�ģ�������Overload��equals������
    //   @Override
//   public boolean equals(Object obj)
//    {
//        return ((MyTestClass)obj).Value==this.Value;
//    }

    public MyTestClass(int initValue) {
        Value = initValue;
    }

    public boolean equals(MyTestClass obj) {
        return obj.Value == this.Value;
    }
}
