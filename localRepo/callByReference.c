#include <stdio.h>

void areaOfRectangle (int* ptr1, int* ptr2,int* ptr3) { 
    *ptr3 = (*ptr1) * (*ptr2);
}
int main () {
    int l,w;
    scanf("%d %d",&l,&w);
    int area = 0;
    areaOfRectangle (&l,&w,&area);
    printf("area = %d",area);
    return 0;
}