#include <stdio.h>

int main ()
{
    int a,b;
    char ch;

    scanf("%d %c %d",&a,&ch,&b);

    switch (ch) {

        case '<':

            if (a < b) {

                printf("Right\n");

            } else {

                printf("Wrong\n");

            }

            break;

        case '>':

            if (a > b){

                printf("Right\n");

            } else {

                printf("Wrong\n");

            }

            break;

        case '=':

            if (a == b) {

                printf("Right\n");

            } else {

                printf("Wrong\n");

            }

            break;

        default :

            break;

    }

    return 0;

}
