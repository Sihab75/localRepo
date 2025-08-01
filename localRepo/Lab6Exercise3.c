#include <stdio.h>
#include <math.h>

int main (){
    int n;
    scanf("%d",&n);
    int a[n],sum = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d",&a[i]);
        sum += a[i];
    }
    float mean = (float)sum / n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1 - i; j++){
            if(a[j] > a[j + 1]) {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
    float sum1 = 0;
    for (int i = 0; i < n; i++) {
        float diff =  a[i] - mean;
        sum1 = sum1 + diff * diff;
    }
    float av = sum1 / n;
    float sd = sqrt(av);
    int first = 0,end = n - 1;
    float mid = a[0];
    while (first < end) {
        if (n % 2 == 0){
            mid = (a[first] + a[end]) / 2.00;
        } else {
            mid = a[first + 1];
        }
        first++;
        end--;
    }


    printf("mean = %.2f\nmedian = %.2f\nStandard Deviation = %.2f",mean,mid,sd);

    return 0;

}