#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* next;
};
int main () {
    struct node* head = NULL;
    struct node* second = NULL;
    struct node* third = NULL;
    head = (struct node*) malloc (sizeof(struct node));
    second = (struct node*) malloc (sizeof(struct node));
    third = (struct node*) malloc (sizeof(struct node));
    (*head).data = 12;
    (*head).next = second;
    (*second).data = 20;
    (*second).next = third;
    (*third).data = 40;
    (*third).next = NULL;
    struct node* temp = head;
    while (temp != NULL) {
        printf("%d",(*temp).data);
        if ((*temp).next != NULL) {
            printf(" -> ");
        }
        temp = (*temp).next;
    }
    printf("\n");
    return 0;
}