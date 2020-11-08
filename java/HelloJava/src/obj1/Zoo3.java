package obj1;


public class Zoo {

    public static void main(String args[]) {
        Feeder f = new Feeder("С��");
        Animal[] ans = new Animal[16];

        //����ԱС��ι��һֻʨ��
        ans[0] = new Lion();
        //����ԱС��ι��ʮֻ����
        for (int i = 0; i < 10; i++) {
            ans[1 + i] = new Monkey();
        }
        //����ԱС��ι��5ֻ����
        for (int i = 0; i < 5; i++) {
            ans[11 + i] = new Pigeon();
        }

        f.feedAnimals(ans);
    }
}

class Feeder {

    public String name;

    Feeder(String name) {
        this.name = name;
    }

    public void feedAnimals(Animal[] ans) {
        for (Animal an : ans) {
            an.eat();
        }
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
