#include <iostream>
using namespace std;

class Queue {
    int q[10];
    int n = 10;
    int rear = -1, front = -1;
public :
    void enqueue (int val) {
        if (rear == n - 1) {
            cout << "queue is full !" << endl;
            return;
        }
        if (rear == -1) {
            front = 0;
        }
        rear++;
        q[rear] = val;
    }

    void dequeue () {
        if (rear == - 1 || front == -1) {
            cout << "Queue is empty " << endl;
            return;
        }
        if (rear == front) {
            rear = - 1, front = -1;
            return;
        }
        front++;
    }
    void Display () {
        for (int i = front; i <= rear; i++) {
            cout << q[i] << ' ';
        }
        cout << endl;
    }
    int getfront () {
        return q[front];
    }
};

int main () {
    Queue q;
    q.enqueue (10);
    q.enqueue (20);
    q.enqueue (30);
    q.enqueue (40);
    q.enqueue (50);
    q.enqueue (60);
    q.enqueue (70);
    q.Display ();
    q.dequeue ();
    q.Display ();
    cout << q.getfront () << endl;
    return 0;
}
