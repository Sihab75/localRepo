#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* next;
}*front == NULL, *rear = NULL;

void enqueue (int val) {
    struct node* newNode = (struct node*) malloc (sizeof (struct node));
    newNode->data = val;
    newNode->next = NULL;
    if (front == NULL) {
        front = rear = newNode;
        rear
        return;
    }
    re
}