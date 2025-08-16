#include <stdio.h> 

int  fibonacci(int n) {
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    return fibonacci(n - 1) + fibonacci (n - 2);
}
int main () {
    int n;
    scanf("%d",&n);
    if (n < 0) {
        printf("fibonacci not define negative numer\n");
        return 0;
    }
    printf("Fibonacci Number position %dth is %d\n",n,fibonacci(n));
    return 0;
}