#include <stdio.h>
int revers (int n, int ans) {
    if (n <= 0) {
        return ans;
    }
    return revers (n / 10, ans * 10 + n % 10);
}
int main () {
    int n;
    scanf("%d",&n);
    printf("%d\n",revers(n,0));
    return 0;
}