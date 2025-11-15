#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* next;
    struct node* prev;
};

struct node* insertAtEnd (struct node* head, int val) {
    struct node* newNode = NULL;
    newNode = (struct node*) malloc (sizeof(struct node));
    newNode->data = val;
    newNode->next = NULL;
    newNode->prev = NULL;
    if (head == NULL) {
        head =newNode;
    } else {
        struct node* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        newNode->prev = temp;
        temp->next = newNode;
    }
    return head;
}

struct node* deleteAtBeginning(struct node* head) {
    if (head == NULL) {
        return head;
    }
    head = head->next;
    head->prev = NULL;
    return head;
}

struct node* deleteAtend (struct node* head) {
    if (head == NULL) {
        return head;
    }
    struct node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp = temp->prev;
    temp->next = NULL;
    return head;
}

struct node* deleteAtIndex(struct node* head, int pos) {
    if (head == NULL) {
        printf("List is empty.\n");
        return head;
    }

    struct node* temp = head;

    if (pos == 0) {
        head = head->next;
        if (head != NULL)
            head->prev = NULL;
        free(temp);
        return head;
    }

    int i = 0;
    struct node* prev = NULL;
    while (temp != NULL && i < pos) {
        prev = temp;
        temp = temp->next;
        i++;
    }
    if (temp == NULL) {
        printf("Position out of range.\n");
        return head;
    }

    temp = temp->next;
    prev->next = temp;
    temp->prev = prev;
    return head;
}

void printLinkedList (struct node* head) {
    struct node* temp = head;
    while (temp != NULL) {
        printf("%d",temp->data);
        if (temp->next != NULL) {
            printf("<=>");
        }
        temp = temp->next;
    }
    printf("\n");
}

int main () {
    int n;
    scanf("%d",&n);
    struct node* head = NULL;
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        head = insertAtEnd (head, x);
    }
    printLinkedList (head);
    head = deleteAtBeginning (head);
    printLinkedList (head);
    head = deleteAtend (head);
    printLinkedList (head);
    int c;
    printf("enter your postion : ");
    scanf("%d", &c);
    head = deleteAtIndex (head, c);
    printLinkedList (head);
    return 0;
}