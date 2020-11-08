package obj1;

public class ParentChildTest {
    public static void main(String[] args) {
        Parent parent = new Parent();
        parent.printValue();
        Child child = new Child();
        child.printValue();

        parent = child;
        parent.printValue();

        parent.myValue++;
        parent.printValue();

        ((Child) parent).myValue++;
        parent.printValue();

    }
}

class Parent {
    public int myValue = 100;

    public void printValue() {
        System.out.println("Parent.printValue(),myValue=" + myValue);
    }
}

class Child extends Parent {
    public int myValue = 200;

    public void printValue() {
        System.out.println("Child.printValue(),myValue=" + myValue);
    }
}