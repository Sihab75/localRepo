import java.util.Scanner;
public class Java5 {
    public static void main (String[] args) {
        Scanner sc = new Scanner(System.in);
        int val = sc.nextInt();
        if (val%2==0) {
            System.out.println("The Number is Even");
        } else {
            System.out.println("The Number is Odd");
        }
    }
}