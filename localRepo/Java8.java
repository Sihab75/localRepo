import java.util.Scanner;
public class Java8 {
    public static void main (String[] args) {
        Scanner sc = new Scanner(System.in);
        int x = sc.nextInt();
        if (x==0) {
            System.out.println("The number is Zero");
        } else if (x>0) {
            System.out.println("The Number is Positive");
        } else {
            System.out.println("The Number is Negative");
        }
    }
}