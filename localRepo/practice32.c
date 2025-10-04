#include <stdio.h>
#include <string.h>

int uppercase(char str[],int len) {
    if (len < 0) {
        return 0;
    }
    if (str[len] >= 'a' && str[len] <= 'z') {
        str[len] = str[len] - 32;
    }
    
    return uppercase (str,len - 1);
}

int main () {
    char str[5000];
    scanf("%[^\n]", str);
    uppercase (str, strlen(str) - 1);
    printf("%s\n",str);
    return 0;
}