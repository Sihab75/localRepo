#include <stdio.h>

int main () {
    int number;

    printf("enter a number is : ");
    scanf("%d",&number);

    if (number % 5 == 0 && number % 11 == 0) {
        printf("the number = %d is divisible by 5 and 11\n",number);
    } else {
        printf("the number = %d is not divisible by 5 and 11\n",number);
    }

    return 0;

}