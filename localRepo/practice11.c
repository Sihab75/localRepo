#include <stdio.h>

void swap (int* ptr1, int* ptr2) {
    *ptr1 = *ptr1 + *ptr2;
    *ptr2 = *ptr1 - *ptr2;
    *ptr1 = *ptr1 - *ptr2;
}

int main () {
    int a,b;
    scanf("%d %d",&a,&b);
    swap (&a,&b);
    printf("a = %d\nb = %d\n",a,b);
    return 0;
}