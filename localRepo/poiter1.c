#include <stdio.h>

void swap (int* ptr1,int* ptr2) {
    int temp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = temp;
}

int main () {
    int a,b;
    scanf("%d %d",&a,&b);

    printf("a = %d\n",a);
    printf("b = %d\n",b);
    swap(&a,&b);
    printf("a = %d\n",a);
    printf("b = %d\n",b);
    return 0;
}