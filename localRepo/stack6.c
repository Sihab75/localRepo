#include <stdio.h>
#include <stdlib.h>

struct stack{
    int data;
    struct stack* next;
}*head = NULL;

struct stack* top = NULL;

void push (int val) {
    struct stack* newNode = (struct stack*) malloc (sizeof(struct stack));
    newNode->data = val;
    newNode->next = NULL;
    if (head == NULL) {
        head = newNode;
        top = head;
        return;
    }
    struct stack* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    top = temp->next;
}

int pop () {
    struct stack* temp = head;
    struct stack* prev = NULL;
    while (temp->next != NULL) {
        prev = temp;
        temp = temp->next;
    }
    prev->next = NULL;
    top = prev;
    int val = temp->data;
    free(temp);
    return val;
}

void print (struct stack* temp) {
    if (temp == NULL) {
        return;
    }
    print(temp->next);
    printf("%d ", temp->data);
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
                printf("Top is : %d\n", top->data);
                break;
            case 4:
                print (head);
                printf("\n");
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