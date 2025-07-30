#include <stdio.h>

int main () {
    int pin;
    printf("Welcome to the ATM!\nPlease enter your PIN : ");
    scanf("%d",&pin);
    float amount = 0.00;
    if (pin != 251) {
        printf("Your PIN is Wrong");
        return 0;
    }
    int n;
    do {
        printf("\nATM Menu : \n1. Amount check\n2. deposit\n3. withdraw\n4. Exit\nEnter your choice : ");
        scanf("%d",&n);
        switch(n) {
            case 1: {
                printf("Amount is : %.f\n",amount);
                break;
            }
            case 2: {
                int a;
                printf("Enter your amount to deposit : ");
                scanf("%d",&a);
                amount += a;
                printf("Your amount is : %.2f",amount);
                break;
            }
            case 3: {
                int b;
                printf("Enter amount to withdraw : ");
                scanf("%d",&b);
                if (amount < b){
                    printf("You don't have enough amount.");
                    return 0;
                }
                amount -= b;
                printf("Deposit Complete! your curent amount is : %.2f",amount);
                break;
            }
            case 4: {
                printf("Thank you! Exiting...\n");
                break;
            }
            default: {
                printf("Wrong option 😌");
                return 0;
            }
        }
    } while ( n != 4);
    return 0;
}