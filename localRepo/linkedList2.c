#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* next;
};

int length (struct node* head) {
    struct node* temp = head;
    int count = 0;
    while (temp != NULL) {
        count ++;
        temp = temp->next;
    }

    return count;
}

struct node* creation (int val) {
    struct node* newNode = NULL;
    newNode = (struct node*) malloc (sizeof(struct node));
    newNode->data = val;
    newNode->next = NULL;
    return newNode; 
}

int main () {
    int n;
    scanf ("%d", &n);
    struct node* head = NULL;
    head = (struct node*) malloc (sizeof(struct node));
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d",&x);
        head = creation (x);
    }

    int len = length (head);
    printf("%d\n",len);
    return 0;
}