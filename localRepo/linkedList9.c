#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* next;
};

struct node* insertAtEnd (struct node*  head, int val) {
    struct node* newNode = NULL;
    newNode = (struct node*) malloc (sizeof(struct node));
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

void printLinkedList (struct node* head) {
    struct node* temp = head;
    while (temp != NULL) {
        printf("%d",temp->data);
        if (temp->next != NULL) {
            printf("->");
        }
        temp= temp->next;
    }
    printf("\n");
}

struct node* reversLinkedList (struct node* head) {
    struct node* prev = NULL;
    struct node* current = head;
    struct node* next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    head = prev;
    return head;
}

int main () {
    int n;
    scanf("%d", &n);
    struct node* head = NULL;
    for (int i = 0; i <n; i++) {
        int x;
        scanf("%d", &x);
        head = insertAtEnd (head, x);
    }
    printLinkedList (head);
    head = reversLinkedList(head);
    printLinkedList (head);
    return 0;
}