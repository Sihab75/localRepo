#include <stdio.h>

int main () {
    int n;
    scanf("%d",&n);

    int a[n];
    int even[n],odd[n];
    for (int i = 0; i< n; i++) {
        scanf("%d",&a[i]);
    }
    int i = 0,j = 0,k = 0;
    while (n--){
        if (a[k] % 2 == 0){
            even[i] = a[k];
            i++;
        } else {
            odd[j] = a[k];
            j++;
        }
        k++;
    }
    printf("Even numbers is : ");
    for (int l = 0; l < i; l++) {
        printf("%d ",even[l]);
    }
    printf("\nodd numberes is : ");
    for (int l = 0; l < j; l++) {
        printf("%d ",odd[l]);
    }
    printf("\n");
    return 0;
    
}