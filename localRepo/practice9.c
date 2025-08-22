#include <stdio.h>

int power(int x, int n) {
    if (n <= 1) {
        return x;
    }
    return power (x * x, n - 1);
} 

int main () {
    int n,x;
    scanf("%d %d",&x,&n);
    int p = power (x,n);
    printf("%d ^ %d = %d\n",x, n, p);
    return 0;
}