#include <stdio.h>
#include <math.h> 

int main () {

    int a,c;
    long long b,d;

    scanf("%d %lld %d %lld",&a,&b,&c,&d);

    double A = b * log(a);
    double B = d * log(c);
    
    if (A > B) {

        printf("YES\n");
    
    } else {

        printf("NO\n");

    }

    return 0;

}