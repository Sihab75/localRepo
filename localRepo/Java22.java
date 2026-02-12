import java.util.Scanner;
public class Java22 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter the Size of Array: ");
        int n = sc.nextInt();
        int[] arr = new int[n];
        for(int i=0;i<n;i++)
            arr[i]= sc.nextInt();
        int min = arr[0];
        int max = arr[0];
        int oddNumber = 0, evenNumber = 0;
        for(int i = 0; i < n;i++){
            max = Math.max(max, arr[i]);
            min = Math.min(min,arr[i]);
            if (arr[i]%2==0) evenNumber++;
            else oddNumber++;
        } 
        System.out.println("Maximum on array : "+ max);
        System.out.println("Minimum on Array: "+min);
        System.out.println("Odd Number on Array: "+oddNumber);
        System.out.println("Even Number of Array: "+evenNumber);

    }
}
