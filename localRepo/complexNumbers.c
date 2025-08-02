#include <stdio.h>

struct complex {
    float real;
    float imag;
};

struct complex add(struct complex a, struct complex b){
    struct complex sum;
    sum.real = a.real + b.real;
    sum.imag = a.imag + b.imag;
    return sum;
}

struct complex diff (struct complex a,struct complex b) {
    struct complex sub;
    sub.real = a.real - b.real;
    sub.imag = a.imag - b.imag;
    return sub;
}

struct complex mult (struct complex a,struct complex b){
    struct complex mul;
    mul.real = a.real * b.real - a.imag * b.imag;
    mul.imag = a.real * b.imag + a.imag * b.real;
    return mul;
}

struct complex div (struct complex a,struct complex b){
    struct complex d;
    d.real = (a.real * b.real + a.imag * b.imag) / (b.real * b.real + b.imag * b.imag);
    d.imag = (a.imag * b.real - a.real * b.imag) / (b.real * b.real + b.imag * b.imag);
    return d;
}

void print (struct complex c) {
    if (c.imag < 0){
        printf("%.2f-i%.2f\n",c.real,-c.imag);
    } else {
        printf("%.2f+i%.2f\n",c.real,c.imag);
    }
}

int main (){
    struct complex a,b;

    printf("Enter 1st complex number : ");
    scanf("%f %f",&a.real,&a.imag);

    printf("Enter 2nd complex number : ");
    scanf("%f %f",&b.real,&b.imag);

    // result = add(a,b);
    // printf("%.2f  +  i%.2f\n",result.real,result.imag);
    struct complex sum = add(a,b);
    struct complex sub = diff(a,b);
    struct complex mul = mult(a,b);
    struct complex di = div(a,b);

    printf("Addition = ");
    print(sum);

    printf("Subtraction = ");
    print(sub);

    printf("Multiplication = ");
    print(mul);

    printf("Div = ");
    print(di);

    return 0;

}