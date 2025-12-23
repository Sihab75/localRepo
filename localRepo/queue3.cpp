#include <iostream>
using namespace std;

class Queue {
    int n = 5;
    int arr [5];
    int rear = -1;
    int front = -1;
public:
    void enqueue (int val) {
        if (front == (rear  + 1 % n)) {
            cout << "Queue is full " << endl;
            return;
        }
        if (rear == -1 && front == -1) {
            front = 0;
        }
        rear++;
        rear = rear % n;
        arr[rear] = val;
    }

    void dequeue () {
        if (front == -1 && rear == -1) {
            cout << "Queue is already empty" << endl;
            return;
        }
        if (rear == front) {
            rear = -1;
            front = -1;
            return;
        }
        front++;
        front = front % n;
    }

    void print () {
        if (front == -1 && rear == -1) {
            cout << "Queue is already empty" << endl;
            return;
        }
        int i = front;
        while (i != rear) {
            cout << arr[i] << ' ';
            i++;
            i = i % n;
        }
        cout << arr [i] << endl;
    }
};

int main () {
    Queue q;
    int n, val, choice;
    do {
        printf("1.Enqueue\n2.Dequeue\n3.Display Queue\n4.Exit\nEnter Choice: ");
        scanf ("%d", &choice);
        switch (choice) {
        case 1:
            printf("Enter the Number of Element is : ");
            scanf ("%d", &n);
            printf("Enter Element is : ");
            for (int i = 0; i < n; i++) {
                cin >> val;
                q.enqueue (val);
            }
            break;
        case 2:
            q.dequeue ();
            break;
        case 3:
            q.print ();
            break;
        case 4:
            break;
        default :
            printf("Wrong Choice \n");
            break;
        }
    } while (choice != 4);
    return 0;
} 