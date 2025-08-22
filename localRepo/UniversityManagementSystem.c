#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SEM 12
#define MAX_COURSE 10
#define MAX_STUDENT 100

/*
    University Management System (single-file, menu-driven)
    Files used (created if missing):
    - student.txt  : id, name, cgpa, totalCourse   (per student, newline-separated)
    - course.txt   : for each student: [code, name, credit] repeated totalCourse times
    - password.txt : one line per student: password
    - marks.txt    : one line per student: totalCourse integers (or -1) separated by spaces
*/

// ----------------------------- Globals -----------------------------
FILE *course_f, *student_f, *password_f, *marks_f;
int count_students = 0;

// ----------------------------- Types -----------------------------
struct course {
    char code[50];
    char name[50];
    int credit;
};

struct student {
    int id;
    char name[50];
    char pass[50];
    int mark[10]; // Maximum 10 courses per student
    float cgpa;
    int totalCourse;
    struct course c[10];
};

// ----------------------------- Helpers -----------------------------
static void ensure_files_exist(void) {
    const char *paths[] = { "student.txt", "course.txt", "password.txt", "marks.txt" };
    for (int i = 0; i < 4; i++) {
        FILE *fp = fopen(paths[i], "a");
        if (fp) fclose(fp);
    }
}

static void trim_newline(char *s) {
    s[strcspn(s, "\n")] = 0;
}

// ----------------------------- IO Routines -----------------------------
void inputSWC(struct student s[], int n) {
    for (int i = 0; i < n; i++) {
        printf("Enter Information of Student no.%d \n", i + 1);
        printf("ID : ");
        scanf("%d", &s[i].id);
        getchar();

        printf("Name : ");
        fgets(s[i].name, sizeof(s[i].name), stdin);
        trim_newline(s[i].name);

        printf("CGPA : ");
        scanf("%f", &s[i].cgpa);
        getchar();

        printf("Total Course (<=10): ");
        scanf("%d", &s[i].totalCourse);
        getchar();
        if (s[i].totalCourse < 0) s[i].totalCourse = 0;
        if (s[i].totalCourse > 10) s[i].totalCourse = 10;

        for (int j = 0; j < s[i].totalCourse; j++) {
            printf("Enter the course details :\n");
            printf("Course Code : ");
            fgets(s[i].c[j].code, sizeof(s[i].c[j].code), stdin);
            trim_newline(s[i].c[j].code);

            printf("Course Name : ");
            fgets(s[i].c[j].name, sizeof(s[i].c[j].name), stdin);
            trim_newline(s[i].c[j].name);

            printf("Credit : ");
            scanf("%d", &s[i].c[j].credit);
            getchar();
        }
        printf("Enter Student password : ");
        fgets(s[i].pass, sizeof(s[i].pass), stdin);
        trim_newline(s[i].pass);

        for (int j = 0; j < s[i].totalCourse; j++) s[i].mark[j] = -1;
    }
}

void fileWrite(struct student s[], int n) {
    course_f = fopen("course.txt", "a");
    student_f = fopen("student.txt", "a");
    password_f = fopen("password.txt", "a");
    marks_f   = fopen("marks.txt", "a");

    if (!course_f || !student_f || !password_f || !marks_f) {
        printf("open file failed!\n");
        if (course_f) fclose(course_f);
        if (student_f) fclose(student_f);
        if (password_f) fclose(password_f);
        if (marks_f) fclose(marks_f);
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(student_f, "%d\n%s\n%.2f\n%d\n", s[i].id, s[i].name, s[i].cgpa, s[i].totalCourse);

        for (int j = 0; j < s[i].totalCourse; j++) {
            fprintf(course_f, "%s\n%s\n%d\n", s[i].c[j].code, s[i].c[j].name, s[i].c[j].credit);
        }

        fprintf(password_f, "%s\n", s[i].pass);

        if (s[i].totalCourse > 0) {
            for (int j = 0; j < s[i].totalCourse; j++) {
                fprintf(marks_f, "%d%s", s[i].mark[j], (j + 1 == s[i].totalCourse) ? "\n" : " ");
            }
        } else {
            fprintf(marks_f, "\n");
        }
    }

    fclose(student_f);
    fclose(course_f);
    fclose(password_f);
    fclose(marks_f);
}

void fileRead(struct student s[]) {
    ensure_files_exist();
    student_f = fopen("student.txt", "r");
    course_f  = fopen("course.txt", "r");
    password_f = fopen("password.txt", "r");
    marks_f   = fopen("marks.txt", "r");

    if (!student_f || !course_f || !password_f || !marks_f) {
        printf("open file failed!\n");
        if (student_f) fclose(student_f);
        if (course_f) fclose(course_f);
        if (password_f) fclose(password_f);
        if (marks_f) fclose(marks_f);
        return;
    }

    count_students = 0;
    while (fscanf(student_f, "%d", &s[count_students].id) == 1) {
        fgetc(student_f);
        fgets(s[count_students].name, sizeof(s[count_students].name), student_f);
        trim_newline(s[count_students].name);

        fscanf(student_f, "%f", &s[count_students].cgpa);
        fgetc(student_f);
        fscanf(student_f, "%d", &s[count_students].totalCourse);
        fgetc(student_f);

        for (int j = 0; j < s[count_students].totalCourse; j++) {
            fgets(s[count_students].c[j].code, sizeof(s[count_students].c[j].code), course_f);
            trim_newline(s[count_students].c[j].code);
            fgets(s[count_students].c[j].name, sizeof(s[count_students].c[j].name), course_f);
            trim_newline(s[count_students].c[j].name);
            fscanf(course_f, "%d", &s[count_students].c[j].credit);
            fgetc(course_f);
        }

        fgets(s[count_students].pass, sizeof(s[count_students].pass), password_f);
        trim_newline(s[count_students].pass);

        for (int j = 0; j < s[count_students].totalCourse; j++) {
            if (fscanf(marks_f, "%d", &s[count_students].mark[j]) != 1) {
                s[count_students].mark[j] = -1;
            }
        }

        // Clear the newline
        int ch;
        while ((ch = fgetc(marks_f)) != '\n' && ch != EOF) {}

        count_students++;
        if (count_students >= MAX_STUDENT) break;
    }

    fclose(password_f);
    fclose(student_f);
    fclose(course_f);
    fclose(marks_f);
}

void fileReset(struct student s[]) {
    student_f = fopen("student.txt", "w");
    course_f  = fopen("course.txt", "w");
    password_f = fopen("password.txt", "w");
    marks_f   = fopen("marks.txt", "w");

    if (!student_f || !course_f || !password_f || !marks_f) {
        printf("Open file failed!\n");
        if (student_f) fclose(student_f);
        if (course_f) fclose(course_f);
        if (password_f) fclose(password_f);
        if (marks_f) fclose(marks_f);
        return;
    }

    for (int i = 0; i < count_students; i++) {
        fprintf(student_f, "%d\n%s\n%.2f\n%d\n", s[i].id, s[i].name, s[i].cgpa, s[i].totalCourse);

        for (int j = 0; j < s[i].totalCourse; j++) {
            fprintf(course_f, "%s\n%s\n%d\n", s[i].c[j].code, s[i].c[j].name, s[i].c[j].credit);
        }

        fprintf(password_f, "%s\n", s[i].pass);

        for (int j = 0; j < s[i].totalCourse; j++) {
            fprintf(marks_f, "%d%s", s[i].mark[j], (j + 1 == s[i].totalCourse) ? "\n" : " ");
        }

        if (s[i].totalCourse == 0) fprintf(marks_f, "\n");
    }

    fclose(password_f);
    fclose(student_f);
    fclose(course_f);
    fclose(marks_f);
}

// ----------------------------- Printing -----------------------------
void print_one(struct student s[], int i) {
    printf("ID = %d\n", s[i].id);
    printf("Name = %s\n", s[i].name);
    printf("CGPA = %.2f\n", s[i].cgpa);
    printf("Total Course = %d\n", s[i].totalCourse);

    for (int j = 0; j < s[i].totalCourse; j++) {
        printf("Course Name : %s\tCourse code : %s\n", s[i].c[j].name, s[i].c[j].code);
        printf("Credit : %d\n", s[i].c[j].credit);
    }

    // show marks if any
    if (s[i].totalCourse > 0) {
        printf("Marks: ");
        for (int j = 0; j < s[i].totalCourse; j++) {
            printf("%s=%d%s", s[i].c[j].name, s[i].mark[j], (j + 1 == s[i].totalCourse) ? "\n" : ", ");
        }
    }
}

void printAllStudentBasic(struct student s[]) {
    printf("\n=========== ALL STUDENT INFORMATION ==============\n");
    for (int i = 0; i < count_students; i++) {
        printf("Information of student no.%d\n", i + 1);
        printf("Name = %s\n", s[i].name);
        printf("ID = %d\n", s[i].id);
        printf("CGPA = %.2f\n", s[i].cgpa);
    }
}

void printAllStudentWithCourse(struct student s[]) {
    for (int i = 0; i < count_students; i++) {
        print_one(s, i);
        printf("----------------------------------------\n");
    }
}

// ----------------------------- Mutations -----------------------------
void update(struct student s[]) {
    int choice;
    do {
        printf("1.Update Name\n");
        printf("2.Update CGPA \n");
        printf("3.Update Courses\n");
        printf("4.Exit\n");
        printf("Enter Your Choice : ");
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n'); // Clear input buffer
            return;
        }

        switch (choice) {
            case 1: {
                int Id; int found = 0;
                printf("Enter student ID : ");
                scanf("%d", &Id);
                getchar();

                for (int i = 0; i < count_students; i++) {
                    if (Id == s[i].id) {
                        printf("Enter New Name : ");
                        fgets(s[i].name, sizeof(s[i].name), stdin);
                        trim_newline(s[i].name);
                        found = 1;
                        break;
                    }
                }
                if (!found) printf("Not registered.\n");
                break;
            }
            case 2: {
                int Id; int found = 0;
                printf("Enter Student ID : ");
                scanf("%d", &Id);
                getchar();

                for (int i = 0; i < count_students; i++) {
                    if (Id == s[i].id) {
                        printf("Enter New CGPA: ");
                        scanf("%f", &s[i].cgpa);
                        getchar();
                        found = 1;
                        break;
                    }
                }
                if (!found) printf("Not registered.\n");
                break;
            }
            case 3: {
                int Id; int found = 0;
                printf("Enter Student ID : ");
                scanf("%d", &Id);
                getchar();

                for (int i = 0; i < count_students; i++) {
                    if (Id == s[i].id) {
                        printf("Enter New Total Course (<=10): ");
                        int newT;
                        scanf("%d", &newT);
                        getchar();
                        if (newT < 0) newT = 0;
                        if (newT > 10) newT = 10;
                        s[i].totalCourse = newT;

                        for (int j = 0; j < s[i].totalCourse; j++) {
                            printf("Enter Course Code : ");
                            fgets(s[i].c[j].code, sizeof(s[i].c[j].code), stdin);
                            trim_newline(s[i].c[j].code);
                            printf("Enter Course Name : ");
                            fgets(s[i].c[j].name, sizeof(s[i].c[j].name), stdin);
                            trim_newline(s[i].c[j].name);
                            printf("Enter Course Credit : ");
                            scanf("%d", &s[i].c[j].credit);
                            getchar();
                            s[i].mark[j] = -1;
                        }
                        found = 1;
                        break;
                    }
                }
                if (!found) printf("Not registered.\n");
                break;
            }
            case 4:
                break;
            default:
                printf("Wrong Choice!\n");
        }
    } while (choice != 4);
    printf("DONE!\n");
}

void deleteInformation(struct student s[]) {
    int id;
    printf("Enter student ID : ");
    scanf("%d", &id);
    getchar();

    int w = 0;
    for (int r = 0; r < count_students; r++) {
        if (s[r].id != id) {
            if (w != r) s[w] = s[r];
            w++;
        }
    }

    if (w == count_students) {
        printf("ID not found.\n");
        return;
    }

    count_students = w;
    fileReset(s);
    printf("Record deleted.\n");
}

int search(struct student s[]) {
    int id;
    printf("Enter Student ID : ");
    scanf("%d", &id);

    for (int i = 0; i < count_students; i++) {
        if (id == s[i].id) {
            print_one(s, i);
            return 0;
        }
    }

    printf("Not registered.\n");
    return 1;
}

int login(struct student s[], int id, const char *pass) {
    for (int i = 0; i < count_students; i++) {
        if (id == s[i].id) {
            if (strcmp(pass, s[i].pass) == 0) return i;
            printf("Invalid password!\n");
            return -1;
        }
    }
    printf("Not registered.\n");
    return -1;
}

float finalCGPA(int oldCredit, int newCredit, float oldCGPA, float newCGPA) {
    if (oldCredit + newCredit == 0) return 0.0f;
    return ((oldCredit * oldCGPA + newCredit * newCGPA) / (oldCredit + newCredit));
}

void inputMark(struct student s[], int i) {
    printf("Name = %s\nID = %d\n", s[i].name, s[i].id);

    int totalCredits = 0;
    int totalWeightedMarks = 0;

    for (int j = 0; j < s[i].totalCourse; j++) {
        printf("Enter Marks Of %s : ", s[i].c[j].name);
        scanf("%d", &s[i].mark[j]);

        if (s[i].mark[j] < 0) s[i].mark[j] = 0;
        if (s[i].mark[j] > 100) s[i].mark[j] = 100;

        totalWeightedMarks += s[i].mark[j] * s[i].c[j].credit;
        totalCredits += s[i].c[j].credit;
    }

    // CGPA recalc (100 marks = 4.0 scale)
    if (totalCredits > 0)
        s[i].cgpa = (float)totalWeightedMarks / totalCredits / 20.0;
    else
        s[i].cgpa = 0.0;

    printf("Updated CGPA: %.2f\n", s[i].cgpa);
    fileReset(s);
}

// ----------------------------- Portals -----------------------------
void studentPortal(struct student s[]) {
    int id;
    char pass[50];

    printf("Enter Student ID: ");
    scanf("%d", &id);
    getchar();

    printf("Enter Password: ");
    fgets(pass, sizeof(pass), stdin);
    trim_newline(pass);

    int idx = login(s, id, pass);
    if (idx < 0) {
        printf("Login Failed!\n");
        return;
    }

    int choice;
    do {
        printf("\n=== Student Portal ===\n");
        printf("1. View Profile\n");
        printf("2. View Courses\n");
        printf("3. View Marks\n");
        printf("4. Exit\n");
        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                print_one(s, idx);
                break;
            case 2:
                for (int j = 0; j < s[idx].totalCourse; j++) {
                    printf("Course: %s (Code: %s, Credit: %d)\n",
                           s[idx].c[j].name, s[idx].c[j].code, s[idx].c[j].credit);
                }
                break;
            case 3:
                for (int j = 0; j < s[idx].totalCourse; j++) {
                    printf("%s: %d\n", s[idx].c[j].name, s[idx].mark[j]);
                }
                break;
            case 4:
                printf("Logout Successful.\n");
                break;
            default:
                printf("Invalid Choice!\n");
        }
    } while (choice != 4);
}

void teacherPortal(struct student s[]) {
    int choice;
    do {
        printf("\n=== Teacher Portal ===\n");
        printf("1. Input Marks\n");
        printf("2. Search Student\n");
        printf("3. Exit\n");
        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int id;
                printf("Enter Student ID: ");
                scanf("%d", &id);

                int found = 0;
                for (int i = 0; i < count_students; i++) {
                    if (id == s[i].id) {
                        inputMark(s, i);
                        found = 1;
                        break;
                    }
                }
                if (!found) printf("Student Not Found!\n");
                break;
            }
            case 2:
                search(s);
                break;
            case 3:
                printf("Exiting Teacher Portal.\n");
                break;
            default:
                printf("Invalid Choice!\n");
        }
    } while (choice != 3);
}

void adminPortal(struct student s[]) {
    int choice;
    do {
        printf("\n=== IT/Admin Control Panel ===\n");
        printf("1. Add New Student\n");
        printf("2. Update Student Info\n");
        printf("3. Delete Student Info\n");
        printf("4. View All Students (Basic)\n");
        printf("5. View All Students (Detailed)\n");
        printf("6. Exit\n");
        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int n;
                printf("How many students to add? ");
                scanf("%d", &n);
                getchar();

                if (n <= 0) break;

                struct student temp[100];
                if (n > 100) n = 100;

                inputSWC(temp, n);

                for (int k = 0; k < n; k++) {
                    if (count_students < MAX_STUDENT) {
                        s[count_students] = temp[k];
                        count_students++;
                    }
                }

                fileWrite(temp, n);
                printf("%d student(s) added.\n", n);
                break;
            }
            case 2:
                update(s);
                break;
            case 3:
                deleteInformation(s);
                break;
            case 4:
                printAllStudentBasic(s);
                break;
            case 5:
                printAllStudentWithCourse(s);
                break;
            case 6:
                printf("Exiting Admin Portal.\n");
                break;
            default:
                printf("Invalid Choice!\n");
        }
    } while (choice != 6);
}

void billingPortal(struct student s[]) {
    int id;
    printf("Enter Student ID: ");
    scanf("%d", &id);

    for (int i = 0; i < count_students; i++) {
        if (id == s[i].id) {
            int totalCredit = 0;
            for (int j = 0; j < s[i].totalCourse; j++) {
                totalCredit += s[i].c[j].credit;
            }

            int feePerCredit = 1000;
            int totalFee = totalCredit * feePerCredit;

            printf("Student: %s\n", s[i].name);
            printf("Total Courses: %d\n", s[i].totalCourse);
            printf("Total Credits: %d\n", totalCredit);
            printf("Bill (Taka): %d\n", totalFee);
            return;
        }
    }

    printf("Student Not Found!\n");
}

// ----------------------------- Main -----------------------------
int main(void) {
    struct student s[MAX_STUDENT];
    ensure_files_exist();
    fileRead(s);

    int choice;
    do {
        printf("\n===== University Management System =====\n");
        printf("1. Student Portal\n");
        printf("2. Teacher Portal\n");
        printf("3. Admin/IT Control Panel\n");
        printf("4. Billing/Account Management\n");
        printf("5. Exit\n");
        printf("Enter Choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("\nGoodbye.\n");
            break;
        }

        switch (choice) {
            case 1:
                studentPortal(s);
                break;
            case 2:
                teacherPortal(s);
                break;
            case 3: {
                char pass[50];
                printf("Enter Admin Password: ");
                scanf("%s", pass);

                if (strcmp(pass, "gub") != 0) {
                    printf("Invalid password! Access Denied.\n");
                    break;
                }

                adminPortal(s);
                break;
            }
            case 4:
                billingPortal(s);
                break;
            case 5:
                printf("Thank you for using UMS!\n");
                break;
            default:
                printf("Invalid Choice!\n");
        }
    } while (choice != 5);

    return 0;
}
