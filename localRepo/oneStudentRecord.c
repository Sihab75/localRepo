#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

struct student {
    int id;
    char name[50];
    float cgpa;
};

int main () {
    struct student s1,s2;
    printf("Enter ID : ");
    scanf("%d",&s1.id);
    getchar();

    printf("Enter student name : ");
    fgets(s1.name,sizeof(s1.name),stdin);
    s1.name[strcspn(s1.name,"\n")] = 0;

    printf("Enter CGPA : ");
    scanf("%f",&s1.cgpa);
    getchar();

    FILE *student = fopen("oneStudentRecord.txt","w");
    if (student == NULL) {
        printf("Error open file!");
        return 0;
    }

    fprintf(student,"%d\n%s\n%f\n",s1.id,s1.name,s1.cgpa);
    fclose(student);

    student = fopen("oneStudentRecord.txt","r");
    if (student == NULL) {
        printf("Error open file!");
        return 0;
    }
    fscanf(student,"%d",&s2.id);
    fgetc(student);
    fgets(s2.name,sizeof(s2.name),student);
    fscanf(student,"%f",&s2.cgpa);
    fgetc(student);
    fclose(student);

    printf("\nRead From file\n");
    printf("ID = %d\n",s2.id);
    printf("Name = %s",s2.name);
    printf("CGPA = %.2f\n",s2.cgpa);
    return 0;
}