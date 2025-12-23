#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* next;
}*front = NULL, *rear = NULL;

void enqueue (int val) {
    struct node* newNode = (struct node*) malloc (sizeof (struct node));
    newNode->data = val;
    newNode->next = NULL;
    if (rear == NULL && front == NULL) {
        front = rear = newNode;
        return;
    }
    rear->next = newNode;
    rear = rear->next;
} 
void dequeue () {
    if (front == NULL || rear == NULL) {
        printf("Queue is empty\n");
        return;
    }
    struct node* temp = front;
    if (front == rear) {
        front = rear = NULL;
        free(temp);
        return;
    }
    front = front->next;
    free(temp);
}
void print () {
    struct node* temp = front;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main () {
    int n, val, choice;
    do {
        printf("1.Enqueue\n2.Dequeue\n3.Display front and rear value\n4.Display Queue\n5.Exit\nEnter Choice: ");
        scanf ("%d", &choice);
        switch (choice) {
        case 1:
            printf("Enter the Number of Element is : ");
            scanf ("%d", &n);
            printf("Enter Element is : ");
            for (int i = 0; i < n; i++) {
                scanf("%d", &val);
                enqueue (val);
            }
            break;
        case 2:
            dequeue ();
            break;
        case 3:
            printf("Front Value is : %d\nRear Value is : %d\n", front->data, rear->data);
            break;
        case 4:
            print ();
            break;
        default :
            printf("Wrong Choice \n");
            break;
        }
    } while (choice != 5);
    return 0;
} 