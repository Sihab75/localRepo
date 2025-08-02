#include <stdio.h>
#include <string.h>
#include <conio.h>
struct student {
    int id;
    char name[50];
    float cgpa;
};

int main (){
    int n;
    printf("Enter number of student : ");
    scanf("%d",&n);
    getchar();

    struct student s[n];

    for (int index = 0; index < n; index++) {
        
        printf("Enter ID of student no. %d : ",index + 1);
        scanf("%d",&s[index].id);
        getchar();

        printf("Enter name of student no. %d : ",index + 1);
        fgets(s[index].name, sizeof(s[index].name),stdin);
        s[index].name[strcspn(s[index].name,"\n")] = 0;

        printf("Enter CGPA of student no. %d : ",index + 1);
        scanf("%f",&s[index].cgpa);
        getchar();

    }

    printf("\n\n========= STUDENT INFOTMATION ===========\n\n");

    for (int index = 0; index < n; index++) {
        printf("--------STUDENT NO. %d --------\n",index + 1);
        printf("ID = %d\n",s[index].id);
        printf("Name = %s\n",s[index].name);
        printf("CGPA = %.2f\n",s[index].cgpa);
    }

    return 0;

}