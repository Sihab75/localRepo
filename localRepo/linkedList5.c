#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* next;
};

struct node* insertAtIndex (struct node* head, int idx, int val) {
    struct node* newNode = NULL;
    newNode = (struct node*) malloc (sizeof(struct node));
    newNode->data = val;
    newNode->next = NULL;
    if (idx == 0) {
        newNode->next = head;
        head = newNode;
        return head;
    }
    struct node* temp = head;
    int i = 0;
    while (i < idx - 1 && temp != NULL) {
        temp = temp->next;
        i++;
    }
    if (temp == NULL) {
        free(newNode);
        return head;
    }
    newNode->next = temp->next;
    temp->next = newNode;
    return head;
}
struct node* insertAtEnd (struct node* head, int val) {
    struct node* newNode = (struct node*) malloc (sizeof(struct node));
    newNode->data = val;
    newNode->next = NULL;
    if (head == NULL) {
        head = newNode;
    } else {
        struct node* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    return head;
}
void printLikedList (struct node* head) {
    struct node* temp = head;
    while (temp != NULL) {
        printf("%d", temp->data);
        if (temp->next != NULL) {
            printf("->");
        }
        temp = temp->next;
    }
    printf("\n");
}

int main () {
    int n;
    scanf("%d", &n);
    struct node* head = NULL;
    for (int i = 0; i < n; i++) {
        int c;
        scanf("%d", &c);
        head = insertAtEnd(head, c);
    }
    printLikedList (head);
    int idx;
    printf("enter the index no.: ");
    scanf("%d", &idx);
    printf("enter the value : ");
    int x;
    scanf("%d",&x);
    head = insertAtIndex (head, idx, x);
    printLikedList (head);
    return 0;
}