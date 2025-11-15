#include <stdio.h>
#include <stdbool.h>

int  push (int stack[], int max, int top,int val) {
    if (top <= max - 1) {
        top++;
        stack[top] = val;
        printf("%d push to stack\n", val);
    } else {
        printf("stack stack\n");
    }
    return top;
}

int pop(int stack[], int* top) {
    if (*top == -1) {
        printf("Stack Underflow! Cannot pop.\n");
        return -1; 
    } else {
        int value = stack[*top];
        (*top)--;
        return value;
    }
}
int peek (int stack[], int top) {
    if (top == -1) {
        printf("stack is empty!");
        return -1;
    }
    return stack[top];
}

bool isEmpty (int top) {
    if (top == -1) {
        return true;
    }
    return false;
}
bool isFull (int top, int n) {
    if (top == n - 1) {
        return true;
    }
    return false;
}

int main () {
    int n;
    scanf("%d", &n);
    int stack[n];
    int top = -1;
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        top = push (stack, n, top, x);
    }

    int x = pop (stack, &top);
    printf("pop = %d\n", x);
    int pik = peek (stack, top);
    printf("peek = %d\n", pik);
    if (isEmpty(top)) {
        printf("stack is empty\n");
    } else {
        printf("stack not empty\n");
    }
    if (isFull(top, n)) {
        printf("Stack is Full\n");
    } else {
        printf("stack not Full");
    }
    return 0;
}