#include <stdio.h>

int main () {
    int n;
    scanf("%d",&n);
    int temp = n;
    int end = temp % 10;
    temp = temp - end;
    int st, mid = 0,pow = 1;

    while (temp != 0) {
        st = temp % 10;
        temp /= 10;
    }
    int temp1 = n - end;
    while (temp1 > 10) {
        mid = mid + (temp1 % 10) * pow;
        pow *= 10;
        temp1 /=10;
    }
    int revers = end * pow + mid + st;
    printf("%d\n",revers);
    return 0;
    
}