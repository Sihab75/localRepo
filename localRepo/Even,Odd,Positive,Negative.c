#include <stdio.h>

int main () {

    int n;

    scanf("%d",&n);

    int odd = 0,even = 0,positive = 0,negative = 0,num;

    for(int i = 1;i <= n;i++) {

        scanf("%d",&num);

        if (num % 2 == 0) {

            even ++;

        } else {

           odd++;

        }

        if (num > 0) {

            positive++;

        } else if (num < 0) {

            negative++;

        }

    }

    printf("Even: %d\n",even);
    printf("Odd: %d\n",odd);
    printf("Positive: %d\n",positive);
    printf("Negative: %d\n",negative);

    return 0;

}
