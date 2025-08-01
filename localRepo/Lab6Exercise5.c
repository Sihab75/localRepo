#include <stdio.h>

int main (){
    int n;
    scanf("%d",&n);
    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d",&a[i]);
    }
    for (int i = 0; i < n; i++){
        int counted = 1;
        for (int k = 0; k < i; k++){
            if (a[i] == a[k]) {
                counted = 0;
                break;
            }
        }
        if (counted) {
            int count = 0;
            for (int j = i; j < n; j++){
                if (a[i] == a[j]) {
                    count++;
                }
            }
            printf("%d ==== %d\n",a[i],count);
        }
    }
    return 0;
}