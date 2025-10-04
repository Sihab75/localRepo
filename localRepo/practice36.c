#include <stdio.h>
#include <string.h>

struct student {
    int id;
    char name[50];
    float mark;
};

int main () {
    struct student s[5];
    for (int i = 0; i < 5; i++) {
        printf("Enter student no.%d\n", i + 1);
        printf("ID: ");
        scanf("%d",&s[i].id);
        getchar();
        printf("Name : ");
        fgets(s[i].name,sizeof(s[i].name),stdin);
        s[i].name[strcspn(s[i].name, "\n")] = 0;
        printf("Mark : ");
        scanf("%f",&s[i].mark);
    }

    for (int i = 0; i < 5; i++) {
        printf("id : %d\n",s[i].id);
        printf("name : %s",s[i].name);
        printf("mark = %.2f",s[i].mark);
    }
    return 0;
}