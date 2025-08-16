#include <stdio.h>
#include <stdlib.h>
#include<string.h>

FILE *course,*student,*password,*mark;
int count;

struct course {
    int code;
    char name[50];
    int credit;
};
struct student {
    long long id;
    char name[50];
    char pass[50];
    int mark[1000];
    float cgpa;
    int totalCourse;
    struct course c[10];
};

long long intputSWC(struct student s[], int n) {
    for (int i = 0; i < n; i++) {
        printf("Enter Information of Student no.%d \n",i+1);
        printf("ID : ");
        scanf("%lld",&s[i].id);
        getchar();

        printf("Name : ");
        fgets(s[i].name,sizeof(s[i].name),stdin);
        s[i].name[strcspn(s[i].name,"\n")] = 0;

        printf("CGPA : ");
        scanf("%f",&s[i].cgpa);
        getchar();

        printf("Total Course : ");
        scanf("%d",&s[i].totalCourse);
        getchar();

        for (int j = 0; j < s[i].totalCourse; j++){
            printf("Enter the course details :\n");
            printf("Course Code : ");
            scanf("%d",&s[i].c[j].code);
            getchar();

            printf("Course Name : ");
            fgets(s[i].c[j].name,sizeof(s[i].c[j].name),stdin);
            s[i].c[j].name[strcspn(s[i].c[j].name,"\n")] = 0;

            printf("Credit : ");
            scanf("%d",&s[i].c[j].credit);
            getchar();

        }
        printf("Enter Student password : ");
        fgets(s[i].pass,sizeof(s[i].pass),stdin);
        s[i].pass[strcspn(s[i].pass,"\n")] = 0;
    }
    return 0;
}

long long fileWrite(struct student s[],int n){
    course = fopen("course.txt","a");
    student = fopen("student.txt","a");
    password = fopen("password.txt","a");
    if ((course == NULL) || (student == NULL) || (password == NULL)) {
        printf("open file failed!");
        return 0;
    }
    for (int i = 0; i < n; i++) {
        fprintf(student,"%lld\n%s\n%.2f\n%d\n",s[i].id,s[i].name,s[i].cgpa,s[i].totalCourse);
        for (int j = 0; j < s[i].totalCourse; j++){
            fprintf(course,"%d\n%s\n%d\n",s[i].c[j].code,s[i].c[j].name,s[i].c[j].credit);
        }
        fprintf(password,"%s\n",s[i].pass);
    }
    fclose(student);
    fclose(course);
    fclose(password);
    return 0;
}

long long fileRead (struct student s[]) {
    student = fopen("student.txt","r");
    course = fopen("course.txt","r");
    password = fopen("password.txt","r");
    if ((student == NULL) || (course == NULL) || (password == NULL)) {
        printf("open file failed!");
        return 0;
    }
    int i = 0;
    count = 0;
    while (fscanf(student,"%lld",&s[i].id) == 1) {
        fgetc(student);

        fgets(s[i].name,sizeof(s[i].name),student);
        s[i].name[strcspn(s[i].name,"\n")] = 0;

        fscanf(student,"%f",&s[i].cgpa);
        fgetc(student);

        fscanf(student,"%d",&s[i].totalCourse);
        fgetc(student);

        for (int j = 0; j < s[i].totalCourse; j++) {
            fscanf(course,"%d",&s[i].c[j].code);
            fgetc(course);

            fgets(s[i].c[j].name,sizeof(s[i].c[j].name),course);
            s[i].c[j].name[strcspn(s[i].c[j].name,"\n")] = 0;

            fscanf(course,"%d",&s[i].c[j].credit);
            fgetc(course);

        }
        fgets(s[i].pass,sizeof(s[i].pass),password);
        s[i].pass[strcspn(s[i].pass,"\n")] = 0;
        i++;
        count++;
    }
    fclose(password);
    fclose(student);
    fclose(course);
    return 0;
}

long long print(struct student s[],int i) {
    printf("ID = %lld\n",s[i].id);
    printf("Name = %s\n",s[i].name);
    printf("CGPA = %.2f\n",s[i].cgpa);
    printf("Total Course = %d\n",s[i].totalCourse);

    for (int j = 0; j < s[i].totalCourse;j++) {
        printf("Course Name : %s\tCourse code : %d\n",s[i].c[j].name,s[i].c[j].code);
        printf("Credit : %d\n",s[i].c[j].credit);
    }
    return 0;
}

void printAllStudentInformation (struct student s[]) {
    printf("\n=========== ALL STUDENT INFOMATION ==============\n");
    for (int i = 0; i < count; i++) {
        printf("Information of student no.%d\n",i+1);
        printf("Name = %s\n",s[i].name);
        printf("ID = %lld\n",s[i].id);
        printf("CGPA = %.2f\n",s[i].cgpa);
    }
}

void update(struct student s[]) {
    int choice;
    do {
        printf("1.Update Name\n");
        printf("2.Update CGPA \n");
        printf("3.Update Course\n");
        printf("4.Exit\n");
        printf("Enter Your Choice : ");
        scanf("%d",&choice);

        switch (choice) {
            case 1: {
                long long Id;
                int found = 1;
                printf("Enter student ID : ");
                scanf("%lld",&Id);
                getchar ();
                for (int i = 0; i < count; i++) {
                    if (Id == s[i].id) {
                        printf("Enter New Name : ");
                        fgets(s[i].name,sizeof(s[i].name),stdin);
                        s[i].name[strcspn(s[i].name,"\n")] = 0;
                        found = 0;
                        break;
                    }
                }
                if (found) {
                    printf("Not registered.\n");
                }
                
                break;
            }
            case 2: {
                long long id;
                int found = 1;
                printf("Enter Student ID : ");
                scanf("%lld",&id);
                getchar();
                for (int i = 0; i < count; i++) {
                    if (id == s[i].id) {
                        scanf("%f",&s[i].cgpa);
                        getchar();
                        found = 0;
                        break;
                    }
                }
                if (found) {
                    printf("Not registered.\n");
                }
                
                break;
            }
            case 3: {
                long long id;
                int found = 1;
                printf("Enter Student ID : ");
                scanf("%lld",&id);
                getchar();
                for (int i = 0; i < count; i++) {
                    if (id == s[i].id) {
                        for (int j = 0; j < s[i].totalCourse ; j++) {
                            printf("Enter Course Code : ");
                            scanf("%d",&s[i].c[j].code);
                            getchar();
                            printf("Enter Course Name : ");
                            fgets(s[i].c[j].name,sizeof(s[i].c[j].name),stdin);
                            s[i].c[j].name[strcspn(s[i].c[j].name,"\n")] = 0;
                            printf("Enter Course Credit : ");
                            scanf("%d",&s[i].c[j].credit);
                        }
                        found = 0;
                        break;
                    }
                }
                if (found) {
                    printf("Not registered.\n");
                }
                
                break;
            }
            case 4: break;
            default :{
                printf("Wrong Choice!\n");
                return 0;
            }
        }
    } while (choice != 0);
    printf("DONE!\n");

}
void fileReset (struct student s[]) {
    student = fopen("student.txt","w");
    course = fopen("course.txt","w");
    password = fopen("password.txt","w");
    if ((student == NULL) || (course == NULL) || (password == NULL) ) {
        printf("Opent file failed!\n");
        return 0;
    }
    for (int i = 0; i < count; i++) {
        fprintf(student,"%lld\n%s\n%.2f\n%d\n",s[i].id,s[i].name,s[i].cgpa,s[i].totalCourse);
        for (int j = 0; j < s[i].totalCourse; j++) {
            fprintf(course,"%d\n%s\n%d\n",s[i].c[j].code,s[i].c[j].name,s[i].c[j].credit);
        }
        fprintf(password,"%s\n",s[i].pass);
    }
    fclose(password);
    fclose(student);
    fclose(course);
}
void printAllStudentInformationWithCourse(struct student s[]) {
    for(int i = 0; i < count; i++) {
        print(s,i);
    }
}

int deleteInformation (struct student s[]) {
    student = fopen("student.txt","w");
    course = fopen("course.txt","w");
    password = fopen("password.txt","w");
    if ((student == NULL) || (course == NULL) || (password == NULL)) {
        printf("Open file failed!\n");
        return 0;
    }
    long long id;
    printf("Enter student ID : ");
    scanf("%lld",&id);
    getchar();
    for (int i = 0; i < count; i++) {
        if (id != s[i].id) {
            fprintf(student,"%lld\n%s\n%.2f\n%d\n",s[i].id,s[i].name,s[i].cgpa,s[i].totalCourse);
            for (int j = 0; j < s[i].totalCourse; j++) {
                fprintf(course,"%d\n%s\n%d\n",s[i].c[j].code,s[i].c[j].name,s[i].c[j].credit);
            }
            fprintf(password,"%s\n",s[i].pass);
        }
    }
    fclose(password);
    fclose(student);
    fclose(course);

}
int search (struct student s[]) {
    long long id;
    printf("Enter Student ID : ");
    scanf("%lld",&id);
    for (int i = 0; i < count; i++) {
        if (id == s[i].id) {
            print(s,i);
            return 0;
        }
    }
    printf("Not registered.\n");
    return 1;
}

int login (struct student s[],int id,char pass) {
    for (int i = 0; i < count; i++) {
        if (id == s[i].id) {
            if (strcmp(pass,s[i].pass) == 0) {
                return 0;
            }
            printf("invalid password!.");
            return 1;
        }
    }
    printf("Not registered.");
    return 1;
}


float finalCGPA (int oldCredit,int newCredit,float oldCGPA,float newCGPA) {
    return ((oldCredit * oldCGPA + newCredit * newCGPA) / (oldCredit + newCredit));
}

float UpdateCGPA (struct student s[],int i) {
    int sumOfOldCGP = 0;
    for (int j = 0; j < s[i].totalCourse; j++) {
        sumOfOldCGP += s[i].c[j].credit;
    }

}

void inputMark (struct student s[],int i) {
    printf("Name = %s\nID = %lld\n",s[i].name,s[i].cgpa);
    printf("Enter his Mark : ");
    for (int j = 0; j < s[i].totalCourse; j++) {
        printf("Enter Marks Of %s : ",s[i].c[j].name);
        scanf("%d",&s[i].mark[j]);
    }
}

