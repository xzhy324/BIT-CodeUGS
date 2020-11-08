package obj1;

public class ClassAndObjectTest {

    public static void main(String[] args) {
        //创建类的实例，定义一个对象变量引用这一实例
        MyClass obj = new MyClass();
        //通过对象变量调用类的公有方法
        obj.myMethod("Hello");
        //给属性赋值
        obj.setValue(100);
        //输出属性的当前值
        System.out.println(obj.getValue());
        //直接访问对象公有字段
        obj.Information = "Information";
        //输出对象公有字段的当前值
        System.out.println(obj.Information);
    }
}

/**
 * 自定义Java类的示例
 */
class MyClass {
    // 公有字段
    public String Information = "";
    // 定义属性：私有字段+get方法+set方法
    private int value;

    // 自定义公有Java实例方法
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
