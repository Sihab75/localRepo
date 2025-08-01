#include <stdio.h>

int main () {
    
    int n;
    
    do {
        
        scanf("%d",&n);
        if (n == 1999) {

            printf("Correct\n");

        } else {

            printf("Wrong\n");

        }

    } while (n != 1999);

    return 0;

}
