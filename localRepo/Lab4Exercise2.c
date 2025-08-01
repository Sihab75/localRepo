#include <stdio.h>

int main () {

    int n;

    scanf("%d",&n);

    int j = n;
    int pow = 1,last = n % 10,first;
    int mid = n - last;

    while (n > 0) {

        first = n % 10;
        // pow *= 10;
        n /= 10;
    }

    int i = j / 10;
    while (i > 0) {

        pow *= 10;
        i /= 10;

    }

    int temp = first;
    first = last * pow;
    last = temp;
    mid = mid % pow ;
    int final = first + mid + last;

    printf("%d",final);

    return 0;

}