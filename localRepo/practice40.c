#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define d getchar();


// FILE *fptr;
int count = 0;
struct student {
    int student_id;
    char name[50];
    int age;
    float mark;
};

int Add_student(struct student s[]) {
    int n;
    printf("Enter number of student : ");
    scanf("%d",&n);
    d;
    for (int i = 0; i < n; i++) {
        printf("enter student no. %d :\n", i + 1);
        printf("student id: ");
        scanf("%d",&s[i].student_id);
        d;
        printf("Name: ");
        fgets (s[i].name, sizeof(s[i].name),stdin);
        s[i].name[strcspn(s[i].name, "\n")] = 0;
        printf("age :");
        scanf("%d",&s[i].age);
        d;
        printf("mark: ");
        scanf("%f",&s[i].mark);
        d;
        count++;
    }
    return 0;
}

int Display_student(struct student s[]) {
    for (int i = 0; i < count; i++) {
        printf("id = %d\n", s[i].student_id);
        printf("name = %s\n",s[i].name);
        printf("age = %d\n",s[i].age);
        printf("mark = %.2f\n",s[i].mark);
    }
    return 0;
}

int Search_student(struct student s[]) {
    int id ;
    printf("Enter student id: ");
    scanf("%d",&id);
    d;
    for (int i = 0; i < count; i++) {
        if (id == s[i].student_id) {
            printf("id = %d\n", s[i].student_id);
            printf("name = %s\n",s[i].name);
            printf("age = %d\n",s[i].age);
            printf("mark = %.2f\n",s[i].mark);
        }
    }
    return 0;
}

int Delete_student (struct student s[]) {
    int id;
    printf("Enter id : ");
    scanf("%d",&id);

    for (int i = 0; i < count ; count ++){
        if (id == s[i].student_id) {
            for(int j = i; j < count - 1; count++) {
                s[j] = s[j + 1];
            }
            count --;
            break;
        }
    }
    return 0;

}

int main () {
    struct student s[1000];
    int choice;
    
    do {
        printf("1.add\n2.display\n3.search\n4.delete\n5.exit\n");
        printf("Enter choice: ");
        scanf("%d",&choice);
        d;
        switch (choice) {
            case 1:Add_student(s);
            break;
            case 2: Display_student(s);
            break;
            case 3: Search_student (s);
            break;
            case 4: Delete_student (s);
            break;
            default : 
            break;
        }
    } while (choice != 5);
    return 0;
}