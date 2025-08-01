#include <stdio.h>

int main (){
    long long num1,num2;

    scanf("%lld %lld",&num1,&num2);
    
    int sum = num1 % 10 + num2 % 10;

    printf("%d",sum);

    return 0;

}