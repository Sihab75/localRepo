import java.util.Scanner;
public class Java11 {
    public static void main (String[] args) {
        Scanner sc = new Scanner(System.in);
        long year = sc.nextLong ();
        if ((year%4==0 && year%100 !=0) || (year%400 ==0)) {
            System.out.println("This year is a leap year");
        } else {
            System.out.println("This year is a not leap year");
        }
    } 
}