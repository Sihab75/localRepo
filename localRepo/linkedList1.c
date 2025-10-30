#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* next;
};

struct node* insertNode(struct node* head, int val) {
    struct node* newNode = (struct node*) malloc (sizeof(struct node));
    (*newNode).data = val;
    (*newNode).next = NULL;
    if (head == NULL) {
        head = newNode;
    } else {
        struct node* temp = head;
        while ((*temp).next != NULL) {
            temp = (*temp).next;
        }
        (*temp).next = newNode;
    }
    return head;
}

void printList (struct node* head) {
    struct node* temp = head;
    while (temp != NULL) {
        printf("%d",(*temp).data);
        if ((*temp).next != NULL) {
            printf(" -> ");
        }
        temp = (*temp).next;
    }
    printf("\n");

}
int length (struct node* head) {
    struct node* temp = head;
    int count = 0;
    while (temp != NULL) {
        count++;
        temp = (*temp).next;
    }
    return count;
}

int main () {
    struct node* head = NULL;
    int n;
    printf("enter the Number of element : ");
    scanf("%d",&n);
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d",&x);
        head = insertNode (head, x);
    }
    printList (head);
    printf("%d\n", length(head));
    return 0;
}