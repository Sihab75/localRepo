#include <stdio.h>

int main (){
        float f;

        scanf("%f",&f);

        int i = (int) f;

        if (i == f) {

            printf("int %d",i);

        } else {

            printf("float %d %.3f",i,f-i);

        }

        return 0;

}
