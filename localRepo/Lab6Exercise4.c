#include <stdio.h>

int main () {
    int n;
    scanf("%d",&n);
    int temp = n;
    int a[n],i = 0;
    while (temp > 0){
        a[i] = temp % 2;
        temp /= 2;
        i++;
    }
    while (i--) {
        printf("%d",a[i]);
    }
    return 0;
}