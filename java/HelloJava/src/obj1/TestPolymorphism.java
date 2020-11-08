package obj1;

class Parent {
    public int value = 100;

    public void Introduce() {
        System.out.println("I'm father");
    }

}

class Son extends Parent {
    public int value = 101;

    public void Introduce() {
        System.out.println("I'm son");
    }
}

class Daughter extends Parent {
    public int value = 102;

    public void Introduce() {
        System.out.println("I'm daughter");
    }
}

public class TestPolymorphism {

    public static void main(String args[]) {
        Parent p = new Parent();
        p.Introduce();
        System.out.println(p.value);
        p = new Son();
        p.Introduce();
        System.out.println(p.value);
        p = new Daughter();
        p.Introduce();
        System.out.println(p.value);

    }

}
