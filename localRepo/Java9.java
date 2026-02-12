import java.util.Scanner;
public class Java9 {
    public static void main (String[] args) {
        Scanner sc = new Scanner(System.in);
        float cel = sc.nextFloat();
        double f = (cel/5)*9 + 32;
        System.out.println(f);
    }   
}