#include <stdio.h>
int main (){
    int n;
    scanf("%d",&n);

    int first = 0,second = 1;
    while (first < n) {
        printf("%d ",first);
        int next = first + second;
        first = second;
        second = next;
    }
    return 0;
}