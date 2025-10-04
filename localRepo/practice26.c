#include <stdio.h>

int fibonacci(int n, int first, int second) {
    if (n <= 0) {
        return 0;
    }
    printf("%d ", first);
    return fibonacci (n - 1, second, second + first);
}
int main () {
    int n;
    scanf("%d",&n);
    fibonacci(n,0,1);
    return 0;
}