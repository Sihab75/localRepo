#include <stdio.h>
#define size 9
int queue[size];
int rear = -1;
int front = -1;

void enqueue (int val) {
    if (rear == size -1) {
        printf ("Queue is full\n");
        return;
    }
    if (front == -1) {
        front = 0;
    }
    rear++;
    queue[rear] = val;
}

void dequeue () {
    if (rear == - 1 || front == -1) {
        printf("queue is empty\n");
        return;
    }
    if (rear == front) {
        rear = front = -1;
        return;
    }
    front++;
}

void print () {
    if (rear == -1 || front == -1) {
        printf("Queue is empty\n");
        return;
    }
    for (int i = front; i <= rear; i++) {
        printf("%d ", queue[i]);
    }
    printf("\n");
}

int main () {
    for (int i = 0; i < size; i++) {
        int x;
        scanf("%d", &x);
        enqueue (x);
    }
    print ();
    dequeue ();
    print ();
    return 0;
}