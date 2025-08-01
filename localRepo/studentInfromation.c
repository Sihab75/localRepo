#include <stdio.h>
#include <string.h>

struct student {
    char name[50];
    int id;
    float cgpa;
};

int main (){
    struct student s;

    printf("Enter your name: ");
    fgets(s.name,sizeof(s.name),stdin);

    s.name[strcspn(s.name,"\n")] = 0;

    printf("Enter your id : ");
    scanf("%d",&s.id);

    printf("Enter your CGAPA: ");
    scanf("%f",&s.cgpa);

    printf("\n\n===== STUDENT INFROMATIN =====\n\n");
    printf("Name = %s\n",s.name);
    printf("ID = %d\n",s.id);
    printf("CGPA = %.2f",s.cgpa);

    return 0;
}