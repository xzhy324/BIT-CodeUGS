package basicGrammer;

import java.util.Random;

public class IfStatement {
    public static void main(String[] args) {
        areYouPassed();

        AndOrNot();

        whatIsYourScore();
    }


    //展示条件的组合
    private static void AndOrNot() {
        Random ran = new Random();
        //生成一个[0,100)的随机数
        int ranValue = ran.nextInt(100);
        System.out.println("ranValue=" + ranValue);
        //【或】两个条件，只需要满足一个
        if (ranValue % 3 == 0 || ranValue % 5 == 0) {
            System.out.println("这个数是3或5的倍数");
        }
        //【与】两个条件，必须同时满中
        if (ranValue % 2 == 0 && ranValue > 10) {
            System.out.println("这个数是大于10的偶数");
        }
        //【非】你是白，我就是黑;你是黑，我就是白！
        if (!(ranValue % 2 == 0)) {
            System.out.println("这个数是奇数");
        }
    }

    //考试通过了吗？
    private static void areYouPassed() {
        Random ran = new Random();
        //生成一个[0,100)的随机数
        int score = ran.nextInt(100);
        System.out.println("你Java考了" + score + "分");
        if (score >= 60) {
            System.out.println("恭喜恭喜，你考试及格了！");
        } else {
            System.out.println("杯具了，没过关！");
        }
    }

    //嵌套的条件表达式
    private static void whatIsYourScore(){
        Random ran = new Random();
        //生成一个[0,100)的随机数
        int score = ran.nextInt(100);
        System.out.println("你Java考了" + score + "分");
        if(score<60){
            System.out.println("杯具了，没过关！");
        }else {
            if(score<70){
                System.out.println("好险好险，勉强过关");
            }else{
                if(score<80){
                    System.out.println("考得还算过得去，中不溜");
                }else{
                    if(score<90){
                        System.out.println("考得不错，良！");
                    }else{
                        System.out.println("你是学霸！");
                    }
                }
            }
        }
    }
}
