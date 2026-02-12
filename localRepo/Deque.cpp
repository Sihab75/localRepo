#include <bits/stdc++.h>
using namespace std;
#define max 100

class Deque {
    int arr[max];
    int front, rear, size;
public :
    Deque () {
        front = -1;
        rear = -1;
        size = 0;
    }

    void insertFront (int val) {
        if (size == max) {
            cout << "Deque Overflow" << endl;
        }
        if (size == 0) front = rear = 0;
        else front = (front - 1 + max) % max;
        arr[front] = val;
        size++;
    }

    void insertRear (int val) {
        if (size == max) {
            cout << "Deque Overflow" << endl;
            return;
        }
        if (size == 0) front = rear = 0;
        else rear = (rear + 1) % max;
        arr[rear] = val;
        size++;
    }
    void deleteFront () {
        if (size == 0) {
            cout << "Deque Underflow" << endl;
            return;
        }
        if (front == rear) front = rear = -1;
        else front = (front + 1) % max;
        size--;
    }
    void deleteRear () {
        if (size == 0) {
            cout << "Deque Underflow" << endl;
            return;
        }
        if (front == rear) front = rear = -1;
        else rear = (rear - 1 + max) % max;
        size--;
    }

    void display () {
        int i = front;
        while (i != rear) {
            cout << arr[i] << ' ';
            i = (i+1)%max;
        }
        cout << arr[i] << endl;
    }
};



int main() {
    Deque dq;

    dq.insertRear(10);
    dq.insertRear(20);
    dq.insertFront(5);
    dq.display(); // Output: 5 10 20

    dq.deleteFront();
    dq.display(); // Output: 10 20

    dq.insertFront(3);
    dq.insertRear(25);
    dq.display(); // Output: 3 10 20 25


    dq.deleteRear();
    dq.display(); // Output: 3 10 20

    return 0;
}

