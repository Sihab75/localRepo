import java.util.Scanner;
public class Java16{
    public static void main (String[] args) {
        Scanner Sc = new Scanner(System.in);
        int Digits = Sc.nextInt();
        int count = 0;
        while (Digits > 0) {
            Digits/=10;
            count++;
        };
        System.out.println(count);

    }
}