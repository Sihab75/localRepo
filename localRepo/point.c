#include <stdio.h>
#include <math.h>

struct point {
    float x;
    float y;
};

int main () {
    struct point p1,p2;
    
    printf("enter your 1st (x1,y1): ");
    scanf("%f %f",&p1.x,&p1.y);
    printf("Enter your 2nd point (x2,y2): ");
    scanf("%f %f",&p2.x,&p2.y);


    float sum = pow((p1.x - p2.x),2) + pow((p1.y - p2.y),2);
    float distance = sqrt(sum);

    printf("Distance = %.2f\n",distance);

    return 0;

}