#include <stdio.h>

int maximum (int n,int max) {
    if (n == 0) {
        return max;
    }
    int digits = n % 10;
    if (digits > max) {
        max = digits;
    }
    return maximum (n / 10, max);
}

int main () {
    int n;
    scanf("%d",&n);
    int max = maximum (n,0);
    printf("Maximum digits = %d \n",max);
    return 0;
}