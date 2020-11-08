package obj1;


public class Zoo {

    public static void main(String args[]) {
        Feeder f = new Feeder("小李");
        Animal[] ans = new Animal[16];

        //饲养员小李喂养一只狮子
        ans[0] = new Lion();
        //饲养员小李喂养十只猴子
        for (int i = 0; i < 10; i++) {
            ans[1 + i] = new Monkey();
        }
        //饲养员小李喂养5只鸽子
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
        System.out.println("我不吃肉谁敢吃肉！");
    }
}

class Monkey extends Animal {

    public void eat() {
        System.out.println("我什么都吃，尤其喜欢香蕉。");
    }
}

class Pigeon extends Animal {

    public void eat() {
        System.out.println("我要减肥，所以每天只吃一点大米。");
    }
}
