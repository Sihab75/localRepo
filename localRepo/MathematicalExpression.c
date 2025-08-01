#include <stdio.h>

int main () {
    int a,b,c;
    char ch,ce;

    scanf("%d %c %d %c %d",&a,&ch,&b,&ce,&c);

    switch (ch) {

    case '+':

        if (a + b == c) {

            printf("Yes\n");

        } else {

            printf("%d\n",a + b);

        }

        break;

    case '-':

        if (a - b == c) {

            printf("Yes\n");

        } else {

            printf("%d\n",a - b);

        }

        break;

    case '*':

        if (a * b == c) {

            printf("Yes\n");

        } else {

            printf("%d\n",a * b);

        }

        break;

    default :

        break;

    }

    return 0;

}
