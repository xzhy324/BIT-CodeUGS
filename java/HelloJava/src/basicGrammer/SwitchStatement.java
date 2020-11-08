package basicGrammer;

import java.util.Random;

public class SwitchStatement {
    public static void main(String[] args) {
        useSwitchStatement();
        useSwitchExpression();
    }

    private static void useSwitchStatement() {
        Random ran = new Random();
        //生成一个[0,100)的随机数
        int score = ran.nextInt(100);
        System.out.println("你Java考了" + score + "分");
        //成绩除以10，以便判断此成绩归于哪个成绩组
        int result = score / 10;
        switch (result) {
            case 0, 1, 2, 4, 5:
                System.out.println("杯具了，没过关！");
                break;
            case 6:
                System.out.println("好险好险，勉强过关");
                break;
            case 7:
                System.out.println("考得还算过得去，中不溜");
                break;
            case 8:
                System.out.println("考得不错，良！");
                break;
            default:
                System.out.println("你是学霸！");
        }
    }

    private static void useSwitchExpression() {
        Random ran = new Random();
        //生成一个[0,100)的随机数
        int score = ran.nextInt(100);
        System.out.println("你Java考了" + score + "分");
        //成绩除以10，以便判断此成绩归于哪个成绩组
        int flag = score / 10;
        //switch表达式，会返回一个值作为结果，因此，一定要有default分支
        String result = switch (flag) {
            case 0, 1, 2, 4, 5 -> "杯具了，没过关！";
            case 6 -> "好险好险，勉强过关";
            case 7 -> "考得还算过得去，中不溜";
            case 8 -> "考得不错，良！";
            default -> "你是学霸！";
        };
        System.out.println(result);
    }
}
