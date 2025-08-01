
#include <stdio.h>

int main () {
    int a,b,c;

    scanf("%d %d %d",&a,&b,&c);

    int first = a;
    int second = b;
    int last = c;

    if (first > second){

        int swap = first;
        first = second;
        second = swap;

    }

    if (first > last){

        int swap = first;
        first = last;
        last = swap;

    }

    if (second > last) {

        int swap = second;
        second = last;
        last = swap;

    }

    printf("%d\n%d\n%d\n\n",first,second,last);
    printf("%d\n%d\n%d\n",a,b,c);

    return 0;

}
