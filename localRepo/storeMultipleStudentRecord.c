#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fptr;
int count;

struct student {
    int id;
    char name [50];
    float cgpa;
};

int input (struct student s[], int n) {

    for (int i = 0; i < n; i++) {
        printf("Enter Information of studen No.%d : \n",i + 1);
        printf("ID : ");
        scanf("%d",&s[i].id);
        getchar();
        printf("Name : ");
        fgets(s[i].name,sizeof(s[i].name),stdin);
        s[i].name[strcspn(s[i].name,"\n")] = 0;
        printf("CGPA : ");
        scanf("%f",&s[i].cgpa);
        getchar();
    }
    return 0;
}

int fileWrite(struct student s[],int n) {
    fptr = fopen("StudentInformation.txt","a");
    if (fptr == NULL) {
        printf("File open failed \n");
        return 0;
    }
    for (int i = 0; i < n; i++) {
        fprintf(fptr,"%d\n%s\n%f\n",s[i].id,s[i].name,s[i].cgpa);
    }
    fclose(fptr);
    return 0;
}

int fileRead (struct student s[]) {
    fptr = fopen("StudentInformation.txt","r");
    if (fptr == NULL) {
        printf("File open failed \n");
        return 0;
    }
    int i = 0;
    count = 0;
    while (fscanf(fptr,"%d",&s[i].id) == 1) {
        // fscanf(fptr,"%d",&s[i].id);
        fgetc(fptr);
        fgets(s[i].name,sizeof(s[i].name),fptr);
        s[i].name[strcspn(s[i].name,"\n")] = 0;
        fscanf(fptr,"%f",&s[i].cgpa);
        fgetc(fptr);
        i++;
        count++;
    }
    fclose(fptr);
    return 0;
}

int printing (struct student s[]) {
    printf("\n\n========== STUDENT INFORMATION ==========\n\n");
    for (int i = 0; i < count; i++) {
        printf("Information of Student No.%d\n",i+1);
        printf("ID = %d\n",s[i].id);
        printf("Name = %s\n",s[i].name);
        printf("CGPA = %.2f\n",s[i].cgpa);
    }
    return 0;
}

int main () {
    int n;
    printf("Enter number of student : ");
    scanf("%d",&n);

    struct student s[1000];

    input(s,n);
    fileWrite(s,n);
    fileRead(s);
    printing(s);

    return 0;

}