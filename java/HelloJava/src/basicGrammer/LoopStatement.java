package basicGrammer;

public class LoopStatement {
    public static void main(String[] args) {

        DoWhileLoop();
        whileDoLoop();
        forLoop();

        infiniteDoWhileLoop();
        infiniteForLoop();

        continueInLoop();
    }

    //使用do/while循环输出：1,2,3,4,5,6,7,8,9,10
    private static void DoWhileLoop() {
        int i = 1;
        do {
            if (i != 10)
                System.out.print(i + ",");
            else
                System.out.println(i);
            i++;
        } while (i <= 10);
    }

    //使用do/while循环输出：1,2,3,4,5,6,7,8,9,10
    private static void whileDoLoop() {
        int i = 1;
        while (i <= 10) {
            if (i != 10)
                System.out.print(i + ",");
            else
                System.out.println(i);
            i++;
        }
        ;
    }

    //使用for循环输出：1,2,3,4,5,6,7,8,9,10
    private static void forLoop() {
        for (int i = 1; i <= 10; i++) {
            if (i != 10)
                System.out.print(i + ",");
            else
                System.out.println(i);
        }
    }

    //使用DoWhile实现的“死循环示例”
    private static void infiniteDoWhileLoop() {
        int i = 1;
        do {
            if (i != 10)
                System.out.print(i + ",");
            else
                System.out.println(i);
            i++;
            if (i > 10) break; //终止循环
        } while (true);
    }

    //使用For实现的“死循环示例”
    private static void infiniteForLoop() {
        for (int i = 1; ; i++) {
            if (i > 10) break; //终止循环
            if (i != 10)
                System.out.print(i + ",");
            else
                System.out.println(i);
        }
    }

    //使用continue跳过偶数，只输出奇数:1,3,5,7,9,
    private static void continueInLoop() {
        for (int i = 1; i <= 10; i++) {
            //如果是偶数，提前结束本轮循环
            if (i % 2 == 0) continue;
            System.out.print(i + ",");
        }
    }
}
