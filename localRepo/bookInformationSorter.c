#include <stdio.h>
#include <string.h>
#include <conio.h>

struct book {
    char title[100];
    char author[50];
    int price;
};

int main () {
    int n;
    printf("Enter Number Of Book : ");
    scanf("%d",&n);
    getchar();

    struct book b[n];

    for (int index = 0; index < n; index++){
        printf("====== Book No.%d ======\n",index + 1);

        printf("Enter Book Title : ");
        fgets(b[index].title, sizeof(b[index].title),stdin);
        b[index].title[strcspn(b[index].title,"\n")] = 0;

        printf("Enter Author name : ");
        fgets(b[index].author,sizeof(b[index].author),stdin);
        b[index].author[strcspn(b[index].author,"\n")] = 0;

        printf("Enter the Price of Book : ");
        scanf("%d",&b[index].price);
        getchar();

    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1; j++) {
            if (b[j].price > b[j + 1].price){
                struct book temp = b[j];
                b[j] = b[j + 1];
                b[j + 1] = temp;
            }
        }
    }
    
    printf("\n\n========= BOOK INFORMATION =========\n\n");
    for (int index = 0; index < n; index++){
        printf("Information of Book no.%d\n",index + 1);
        printf("         %s\n",b[index].title);
        printf("\n\n\n\n\n\n    Author is %s\n",b[index].author);
        printf("    price is %d taka\n",b[index].price);
    }

    return 0;

}