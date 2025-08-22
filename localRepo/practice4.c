# include <stdio.h>
# include <ctype.h>

int palindrome (char str[],int end,int found,int st) {
    while (st < end && !isalpha(str[st])) {
        st++;
    }
    while (st < end && !isalpha(str[end])) {
        end--;
    }
    if (st >= end) {
        return found;
    }
    if (tolower(str[st]) != tolower(str[end])) {
        return 0;
    }
    return palindrome (str, end - 1, found, st + 1);
}

int main () {
    char str[500];
    scanf("%[^\n]",str);
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    int found = palindrome(str,len,1,0);

    if (found) {
        printf("is a palindrome\n");
    } else {
        printf("is not palindrome \n");
    }
    return 0;
}