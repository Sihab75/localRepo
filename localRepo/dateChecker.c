#include <stdio.h>
struct date {
    int day;
    int month;
    int year;
};

int main () {
    struct date d;
    
    printf("Enter day = ");
    scanf("%d",&d.day);

    printf("Enter month = ");
    scanf("%d",&d.month);

    printf("Enter year = ");
    scanf("%d",&d.year);

    printf("%02d - %02d - %d\n",d.day,d.month,d.year);

    return 0;
    
}