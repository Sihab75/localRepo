#include <stdio.h>

void fibonacci (int first,int second,int n) {
    if (n <= 0) {
        return;
    }
    printf("%d ",first);
    return fibonacci(second,first + second,n - 1);
}

int main () {
    int n;
    scanf("%d",&n);
    printf("Fibonacci seres : ");
    fibonacci(0,1,n);
    return 0;
}