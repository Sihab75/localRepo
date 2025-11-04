#include <stdio.h>
#include <stdlib.h>

struct node{
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
    struct node* temp = head;
    while (temp != NULL) {
        printf("%d",temp->data);
        if (temp->next != NULL) {
            printf("->");
        }
        temp = temp->next;
    }
    printf("\n");
}
struct node* searchValue (struct node* head, int val) {
    struct node* temp = head;
    while (temp != NULL) {
        if (temp->data == val) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

int main () {
    int n;
    scanf("%d", &n);
    struct node* head = NULL;
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        head = insertAtEnd (head, x);
    }
    printLikedList(head);
    int x;
    printf("enter your finding number : ");
    scanf("%d", &x);
    struct node* ans = searchValue(head, x);
    printf("%p\n",ans);
    return 0;
}