import java.util.Scanner;
public class Java18{
    public static void main (String[] args) {
        Scanner sc = new Scanner(System.in);
        int num = sc.nextInt();
        if (num==1) {
            System.out.println("Not prime");
            return;
        }
        for (int i = 2; i < num/2;i++) {
            if (num%i==0) {
                System.out.println("Not prime");
                return;
            }
        }
        System.out.println("the Number is prime");
    }
}