package obj1;

public class Zoo {

    public static void main(String args[]) {
        Feeder f = new Feeder("С��");
        //����ԱС��ι��һֻʨ��
        f.feedAnimal(new Lion());
        //����ԱС��ι��ʮֻ����
        for (int i = 0; i < 10; i++) {
            f.feedAnimal(new Monkey());
        }
        //����ԱС��ι��5ֻ����
        for (int i = 0; i < 5; i++) {
            f.feedAnimal(new Pigeon());
        }
    }
}

class Feeder {

    public String name;

    Feeder(String name) {
        this.name = name;
    }

    public void feedAnimal(Animal an) {
        an.eat();
    }
}

abstract class Animal {

    public abstract void eat();
}

class Lion extends Animal {

    public void eat() {
        System.out.println("�Ҳ�����˭�ҳ��⣡");
    }
}

class Monkey extends Animal {

    public void eat() {
        System.out.println("��ʲô���ԣ�����ϲ���㽶��");
    }
}

class Pigeon extends Animal {

    public void eat() {
        System.out.println("��Ҫ���ʣ�����ÿ��ֻ��һ����ס�");
    }
}
