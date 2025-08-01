#include <stdio.h>
int main (){
    int  n;
    scanf("%d",&n);
    
    int m[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d",&m[i][j]);
        }
    }
    int tm[n][n];
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            tm [j][i] = m[i][j];
        }
    }
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            printf("%d ",tm[i][j]);
        }
        printf("\n");
    }
    return 0;
}