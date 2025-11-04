#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* next;
};

struct node* insertAtEnd(struct node* head, int val) {
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

int maximumElement (struct node* head) {
    struct node* temp = head;
    int max = temp->data;
    while (temp != NULL) {
        if (max < temp->data) {
            max = temp->data;
        }
        temp = temp->next;
    }
    return max;
}
int minimumElement (struct node* head) {
    struct node* temp = head;
    int min = temp->data;
    while (temp != NULL) {
        if (min > temp->data) {
            min = temp->data;
        }
        temp = temp->next;
    }
    return min;
}

int sumOfAllElement (struct node* head) {
    struct node* temp = head;
    int sum = 0;
    while (temp != NULL) {
        sum += temp->data;
        temp = temp->next;
    }
    return sum;
}

int main () {
    struct node* head = NULL;
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        head = insertAtEnd (head, x);
    }
    printLikedList(head);
    int sum = sumOfAllElement (head);
    printf("%d\n", sum);
    int max = maximumElement (head);
    printf("%d\n", max);
    int min = minimumElement (head);
    printf("%d\n", min);
    return 0;
}