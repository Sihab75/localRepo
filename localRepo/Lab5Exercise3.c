#include <stdio.h>
int main (){
    int n;
    scanf("%d",&n);
    for(int i = 1; i <= n; i++) {
        int digit = 1;
        for (int j = n-i; j >= 1; j--) {
            printf("  ");
        }
        for (int j = 1; j <= i; j++) {
            printf("%4d",digit);
            digit = digit * (i - j) / j;
        }
        printf("\n");
    }
    return 0;
}