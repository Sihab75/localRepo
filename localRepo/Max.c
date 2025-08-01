#include<stdio.h>

int main () {
    
     int n,max = 0,num;
     
     
     scanf("%d",&n);
     
     for (int i = 1;i <= n;i++) {
        
        scanf("%d",&num);
        
        if (num > max) {
            
            max = num;
            
        }
        
     }
     
    printf("%d\n",max);
    
    return 0;
    
}
