#include <stdio.h>

void change(int* ptr){
    scanf("%d",ptr);
}

int main () {
    int n;
    scanf("%d",&n);
    printf("n = %d\n",n);
    change(&n);
    printf("n = %d\n",n);
    return 0;
}