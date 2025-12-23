#include <stdio.h>
int size = 100;
int stack[100];
int top = -1;

void push (int val) {
    if (top == size - 1) {
        printf("Stack is Full\n");
        return;
    }
    top++;
    stack[top] = val;
}

int pop () {
    if (top < 0) {
        printf("Stack is already empty\n");
        return -1;
    }
    int val = stack[top];
    top--;
    return val;
}

void print () {
    for (int i = top; i >= 0; i--) {
        printf("%d ", stack[i]);
    }
    printf("\n");
}

int main () {
    int choice;
    int n;
    int Choice;
    do {
        printf("1.Push in Stack\n");
        printf("2.Pop in Stack\n");
        printf("3.Top in Stack\n");
        printf("4.Display Stack\n");
        printf("5.Arithmetic operation\n");
        printf("6.Exit\n");
        printf("Enter choice is: ");
        scanf ("%d", &choice);
        switch (choice) {
            case 1: 
                printf("Enter Number of Element is : ");
                scanf("%d",&n);
                printf("Enter Element is : ");
                for (int i = 0; i < n; i++) {
                    int x;
                    scanf("%d", &x);
                    push (x);
                }
                printf("Push successfully!\n");
                break;
            case 2:
                printf("Pop successfully! And Pop value is : %d \n", pop());
                break;
            case 3:
                printf("Top is : %d\n", stack[top]);
                break;
            case 4:
                print ();
                break;
            case 5: 
                do {
                    printf("1.Sum\n");
                    printf("2.Sub\n");
                    printf("3.Mul\n");
                    printf("4.Div\n");
                    printf("5.Exit\n");
                    printf("Enter the choice is : ");
                    scanf ("%d", &Choice);
                    switch (Choice) {
                        case 1:
                            push (pop() + pop());
                            break;
                        case 2:
                            push (pop() - pop());
                            break;
                        case 3:
                            push (pop() * pop());
                            break;
                        case 4:
                            push (pop() / pop());
                            break;
                        case 5:
                            break;
                        default :
                            printf("Wrong choice!\n");
                            break;
                    } 
                } while (Choice != 5);
                break;
            case 6:
                break;
            default : 
                printf("Wrong choice!\n");
                break;
        } 
    } while (choice != 6);
    return 0;
}