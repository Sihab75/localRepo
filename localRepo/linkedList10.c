#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* next;
};

struct node* insertAtEnd (struct node* head, int val) {
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

void printLikedList (struct node* head) {
    if (head == NULL) {
        return;
    }
    printf("%d",head->data);
    if (head->next != NULL) {
        printf("->");
    }
    printLikedList (head->next);
}
void printLinkedListRevers (struct node* head) {
    if (head == NULL) {
        return;
    }
    printLinkedListRevers (head->next);
    printf("%d->",head->data);

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
    printLikedList(head);
    printf("\n");
    printLinkedListRevers (head);
    return 0;
}