#include <stdio.h>

int gcd (int a,int b) {
    if (b == 0) {
        return a;
    }
    int revers = a % b;
    return gcd(b,revers);
}

int main () {
    int a,b;
    scanf("%d %d",&a,&b);
    
    if (a < b) {
        int temp = a;
        a = b;
        b = temp;
    }

    int ans = gcd (a,b);
    int lcm = (a * b) / ans;
    printf("GCD = %d\n",ans);
    printf("LCM = %d\n",lcm);
    return 0;
}