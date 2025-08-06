#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fptr;
int count;
struct student {
    int id;
    char name[50];
    float cgpa;
};

int input (struct student s[],int n) {
    for (int i = 0; i < n; i++) {
        printf("Enter Information of student no.%d\n",i + 1);
        printf("student ID : ");
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
        printf("open file failed!\n");
        return 0;
    }
    for (int i = 0; i < n; i++) {
        fprintf(fptr,"%d\n%s\n%.2f\n",s[i].id,s[i].name,s[i].cgpa);
    }
    fclose(fptr);
    return 0;
}

int fileRead (struct student s[]) {
    fptr = fopen("StudentInformation.txt","r");
    if (fptr == NULL) {
        printf("open file failed!\n");
        return 0;
    }
    int i = 0;
    count = 0;
    while (fscanf(fptr,"%d",&s[i].id) == 1) {
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

int print(struct student s[]) {
    printf("\n\n======== All student Information =======\n\n");
    for (int i = 0; i < count; i++) {
        printf("Information of Student No.%d\n",i+1);
        printf("student ID = %d\n",s[i].id);
        printf("Name = %s\n",s[i].name);
        printf("CGPA = %.2f\n",s[i].cgpa);
    }
    return 0;
}

int search(struct student s[],int ID) {
    for (int i = 0; i < count; i++){
        if(ID == s[i].id) {
            printf("student ID = %d\n",s[i].id);
            printf("Name = %s\n",s[i].name);
            printf("CGPA = %.2f\n",s[i].cgpa);
            return 0;
        }
    }
    printf("Not found!\n");
    return 0;
}

int main (){
    int op;
    struct student s[1000];
    do {
        printf("1.Search a Student by ID\n");
        printf("2.Registration new student\n");
        printf("3.view all student information\n");
        printf("4.leave the program\n");
        printf("Enter the option no.: ");
        scanf("%d",&op);
        
        switch (op) {
            case 1: {
                int id;
                printf("Enter to the ID : ");
                scanf("%d",&id);
                fileRead(s);
                search(s,id);
                break;
            }
            case 2:{
                int n;
                printf("Enter the Number of student : ");
                scanf("%d",&n);
                input(s,n);
                fileWrite(s,n);
                break;
            }
            case 3: {
                fileRead(s);
                print(s);
                break;
            }
            case 4: break;
            default : {
                printf("Wrong choice!Out site of program.");
                return 0;
            }

        }

    } while (op != 4);
    printf("thank you!🤗");
    return 0;
}