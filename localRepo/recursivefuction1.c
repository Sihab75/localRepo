#include <stdio.h>

long long fac(int n) {
    if (n == 0 || n == 1) {
        return 1;
    }
    return n * fac(n-1);
}

int main () {
    int n;
    scanf("%d",&n);
    if (n < 0){
        printf("Not factorial\n");
        return 0;
    }
    long long factorial = fac(n);
    
    printf("factorial = %lld\n",factorial);
    return 0;
}