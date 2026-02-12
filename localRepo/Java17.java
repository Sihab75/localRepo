import java.util.Scanner;
public class Java17 {
    public static void main (String[] args){
        Scanner sc = new Scanner (System.in);
        int num = sc.nextInt();
        int newNum = 0;
        while (num>0) {
            newNum = newNum*10 + num%10;
            num/=10;
        }
        System.out.println(newNum);
    }
}