#include <stdio.h>
#include <math.h>
int main () {
    int n;
    scanf("%d",&n);

    int found = 1;
    for (int i = 2; i <= sqrt(n); i++){
        if (n % i == 0){
            found = 0;
            break;
        }
    }
    if (found){
        printf("prime\n");
    } else {
        printf("non prime\n");
    }
    return 0;
}