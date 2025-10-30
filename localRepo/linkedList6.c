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
    if (head ==NULL) {
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
struct node* deleteFromBegining (struct node* head) {
    if (head == NULL) {
        printf("your liked List already empty\n");
        return head;
    } 
    struct node* temp = head;
    head = head->next;
    free(temp);
    return head;
}
struct node* deleteFromEnd (struct node* head) {
    if (head == NULL) {
        printf("list is already empty!");
        return head;
    }
    if (head->next == NULL) {
        free(head);
        return head;
    }
    struct node* temp = head;
    struct node* prev = NULL;
    while (temp->next != NULL) {
        prev = temp;
        temp = temp->next;
    }
    prev->next = NULL;
    free(temp);
    return head;
}
struct node* deleteAtIdx (struct node* head, int idx) {
    if (head == NULL) {
        printf("list is already empty!");
        return head;
    }
    if (idx == 0) {
        struct node* temp = head;
        head = head->next;
        free(temp);
        return head;
    }
    struct node* temp = head;
    struct node* prev = NULL;
    int i = 0;
    while (temp->next != NULL && i < idx) {
        prev = temp;
        temp = temp->next;
        i++;
    }
    prev->next = temp->next;
    free(temp);
    return head;

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
    printLikedList (head);
    head = deleteFromBegining (head);
    printLikedList(head);
    head = deleteFromEnd (head);
    printLikedList (head);
    int idx;
    printf("Enter the index no.: ");
    scanf("%d", &idx);
    head = deleteAtIdx (head, idx);
    printLikedList (head);
    return 0;
}