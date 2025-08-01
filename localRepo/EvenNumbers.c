#include <stdio.h>

int main () {
    int n,found = 1;

    scanf("%d",&n);

    for(int i = 2;i <= n;i = i + 2) {

        printf("%d\n",i);
        found = 0;
    }
    
    if (found) {
        
        printf("-1");
        
    }
    return 0;

}
