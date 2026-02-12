import java.util.Scanner;
public class Java6 {
    public static void main (String[] args) {
        Scanner sc = new Scanner(System.in);
        int x = sc.nextInt();
        int y = sc.nextInt();
        System.out.println("Maximum Is : "+((x>y)?x:y));
    }
}