package obj1;

public class Zoo {
    public static void main(String args[]) {
        Feeder f = new Feeder("小李");
        // 饲养员小李喂养一只狮子
        f.feedLion(new Lion());
        // 饲养员小李喂养十只猴子
        for (int i = 0; i < 10; i++) {
            f.feedMonkey(new Monkey());
        }
        // 饲养员小李喂养5只鸽子
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
        System.out.println("我不吃肉谁敢吃肉！");
    }
}

class Monkey {

    public void eat() {
        System.out.println("我什么都吃，尤其喜欢香蕉。");
    }
}

class Pigeon {

    public void eat() {
        System.out.println("我要减肥，所以每天只吃一点大米。");
    }
}
