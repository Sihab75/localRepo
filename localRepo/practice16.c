#include <stdio.h>

int main () {
    int n;
    scanf("%d",&n);
    int temp =n;
    int freq[10] = {0};
    int count  = 0;
    while ( temp != 0) {
        int digit = temp % 10;
        freq[digit] ++;
        temp /= 10;
        count ++;
    }
    for (int i = 0; i < count; i++) {
        if (freq[i] > 0) {
            printf("%d       %d\n", i, freq[i]);
        }
    }
    return 0;
}