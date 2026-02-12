import java.util.Scanner;
public class Java23{
    public static void main (String[] args){
        Scanner sc = new Scanner(System.in);
        String s = sc.nextLine().toLowerCase();
        int v = 0, c=0;
        for(int i =0; i < s.length();i++) {
            if((s.charAt(i)=='a' || s.charAt(i)=='e'|| s.charAt(i)=='i'||s.charAt(i)== 'o'||s.charAt(i) == 'u') && (s.charAt(i) >= 'a'&& s.charAt(i)<='z')){
                v++;
            } else if (s.charAt(i) >= 'a' && s.charAt(i)<= 'z') c++;
        }
        System.out.println("vowels is : "+v +"\nConsonants: "+ c);
    }
}