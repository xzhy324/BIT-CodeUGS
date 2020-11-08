package obj1;

import java.util.Vector;

public class Zoo {

    public static void main(String args[]) {
        Feeder f = new Feeder("С��");
        Vector<Animal> ans = new Vector<Animal>();

        //����ԱС��ι��һֻʨ��
        ans.add(new Lion());
        //����ԱС��ι��ʮֻ����
        for (int i = 0; i < 10; i++) {
            ans.add(new Monkey());
        }
        //����ԱС��ι��5ֻ����
        for (int i = 0; i < 5; i++) {
            ans.add(new Pigeon());
        }
        f.feedAnimals(ans);
    }
}

class Feeder {

    public String name;

    Feeder(String name) {
        this.name = name;
    }

    public void feedAnimals(Vector<Animal> ans) {
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
