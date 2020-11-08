package obj1;

public class Zoo {
    public static void main(String args[]) {
        Feeder f = new Feeder("С��");
        // ����ԱС��ι��һֻʨ��
        f.feedLion(new Lion());
        // ����ԱС��ι��ʮֻ����
        for (int i = 0; i < 10; i++) {
            f.feedMonkey(new Monkey());
        }
        // ����ԱС��ι��5ֻ����
        for (int i = 0; i < 5; i++) {
            f.feedPigeon(new Pigeon());
        }
    }
}

class Feeder {

    public String name;

    public Feeder(String name) {
        this.name = name;
    }

    public void feedLion(Lion l) {
        l.eat();
    }

    public void feedPigeon(Pigeon p) {
        p.eat();
    }

    public void feedMonkey(Monkey m) {
        m.eat();
    }
}

class Lion {

    public void eat() {
        System.out.println("�Ҳ�����˭�ҳ��⣡");
    }
}

class Monkey {

    public void eat() {
        System.out.println("��ʲô���ԣ�����ϲ���㽶��");
    }
}

class Pigeon {

    public void eat() {
        System.out.println("��Ҫ���ʣ�����ÿ��ֻ��һ����ס�");
    }
}
