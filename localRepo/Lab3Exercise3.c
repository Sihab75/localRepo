#include <stdio.h>

int main (){
    char ch;

    printf("enter a character is : ");
    scanf("%c",&ch);

    if (!(ch >= 'A'&& ch <= 'z')){
        printf("invalid input\n");
        return 0;
    }

    switch (ch) {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
        case 'A':
        case 'E':
        case 'I':
        case 'O':
        case 'U':
            printf("%c is a vowel\n",ch);
            break;
        default:
            printf("%c is a consonant\n",ch);
            break;

    }

    return 0;

}