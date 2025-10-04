#include <stdio.h>

int main () {
    int n;
    scanf("%d",&n);
    int temp = n;
    while (temp !=0) {
        printf("%d",temp%10);
        temp /= 10;
    }
    printf("\n");
    return 0;
}