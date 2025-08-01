#include <stdio.h>

int main () {
    int a,b,c;

    printf("enter three numbers is : ");
    scanf("%d %d %d",&a,&b,&c);

    if(a > b && a > c) {
        printf("%d is the maximum number\n",a);
    } else if (b > c ){
        printf("%d is the maximum number\n",b);
    } else {
        printf("%d is the maximum number\n",c);
    }

    return 0;

}