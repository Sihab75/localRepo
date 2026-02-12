import java.util.Scanner;
public class Java10{
    public static void main (String[] args) {
        Scanner sc = new Scanner (System.in);
        long day = sc.nextLong();
        int year = (int)day/365;
        day = day%365;
        int weeks = (int) day/7;
        day = day%7;
        System.out.println(day+"/"+weeks+"/"+year);
    }
}