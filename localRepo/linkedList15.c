#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* next;
    struct node* prev;
};

struct node* insertAtBegining  (struct node* head, int val) {
    struct node* newNode = NULL;
    newNode = (struct node*) malloc (sizeof(struct node));
    newNode->data = val;
    newNode->next = NULL;
    newNode->prev = NULL;
    if (head == NULL) {
        head = newNode;
    } else {
        newNode->next = head;
        head->prev =  newNode;
        head = newNode;
    }
    return head;
}

struct node* insertAtEnd (struct node* head, int val) {
    struct node* newNode = NULL;
    newNode = (struct node*) malloc (sizeof(struct node));
    newNode->data = val;
    newNode->next = NULL;
    newNode->prev = NULL;
    if (head == NULL) {
        head = newNode;
    } else {
        struct node* temp =head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->prev = temp;
    }
    return head;
}
void printLinkedList (struct node* head) {
    struct node* temp = head;
    while (temp != NULL) {
        printf("%d",temp->data);
        if (temp->next !=NULL) {
            printf("<=>");
        }
        temp = temp->next;
    }
    printf("\n");
}

void traverseBackward (struct node* head) {
    struct node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    while (temp != NULL) {
        printf("%d", temp->data);
        if (temp->prev != NULL) {
            printf("<=>");
        }
        temp = temp->prev;
    }
    printf("\n");
}
struct node* insertAtIndex (struct node* head, int idx, int val) {
    struct node* newNode = NULL;
    newNode = (struct node*) malloc (sizeof(struct node));
    newNode->data = val;
    newNode->next = NULL;
    newNode->prev = NULL;
    if (head == NULL) {
        return head;
    }
    if (idx == 0) {
        newNode->next = head;
        head->prev = newNode;
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
    newNode->prev = temp;
    if (temp->next != NULL) {
        temp->next->prev = newNode;
    }
    temp->next = newNode;
    return head;

}
int main () {
    int n;
    scanf("%d",&n);
    struct node* head = NULL;
    for (int i = 0; i< n;i++) {
        int x;
        scanf("%d",&x);
        head = insertAtEnd (head, x);
    }
    printLinkedList (head);
    traverseBackward (head);
    printf("Enter your insert value is : ");
    int x;
    scanf("%d", &x);
    head = insertAtBegining (head, x);
    printLinkedList (head);
    traverseBackward (head);
    printf("enter your insert index is : ");
    int idx;
    scanf("%d", &idx);
    printf("enter your value is : ");
    int t;
    scanf("%d", &t);
    head = insertAtIndex (head, idx, t);
    printLinkedList (head);
    traverseBackward (head);
    return 0;
}
