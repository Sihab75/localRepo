#include <stdio.h>

int main () {
    int A,B,result;
    char S;

    scanf("%d%c%d",&A,&S,&B);
    switch (S)
    {
    case '+':
        result = A + B;
        printf("%d\n",result);        
        break;
    case '-':
        result = A - B;
        printf("%d\n",result); 
        break;
    case '*':
        result = A * B;
        printf("%d\n",result);
        break;
    case '/':
        if ( B != 0){
            result = A / B;
        printf("%d\n",result);
        } 
        break;
    
    default:
        break;
    }

    return 0;

}
