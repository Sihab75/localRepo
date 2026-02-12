import java.util.Scanner;
public class Java13{
    public static void main (String[] args) {
        Scanner sc = new Scanner (System.in);
        int n=sc.nextInt();
        for (int i =2;i <=n;i+=2) {
            System.out.print(i + " ");
        }
    }
}