#include <stdio.h>

int main() {
    char str[500];
    
    scanf("%[^\n]", str);
    
    char ans[500] = {0};
    int ans_index = 0;
    int i = 0;
    
    while (str[i] != '\0') {
        i++;
    }
    
    int j = 0;
    while (j < i) {
        while (j < i && str[j] == ' ') {
            j++;
        }
        
        int word_start = j;
        while (j < i && str[j] != ' ') {
            j++;
        }
        
        if (ans_index > 0) {
            ans[ans_index] = ' ';
            ans_index++;
        }
        
        for (int k = j - 1; k >= word_start; k--) {
            ans[ans_index] = str[k];
            ans_index++;
        }
    }
    ans[ans_index] = '\0';
    
    printf("%s\n", ans);
    return 0;
}