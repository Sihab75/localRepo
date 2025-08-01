#include <stdio.h>
#include <ctype.h>

int main (){
    char ch;

    scanf("%c",&ch);

    if (ch >= 'A' && ch <= 'Z'){
        ch = tolower(ch);
    }
    
    else if (ch >= 'a' && ch <= 'z'){
        ch = toupper(ch);
    }

    printf("%c\n",ch);

    return 0;

}