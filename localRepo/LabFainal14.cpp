#include <iostream>
using namespace std;

#define SIZE 5

int queue[SIZE];
int front = -1, rear = -1;

// Enqueue (at rear)
void enqueue(int value) {
    if ((rear + 1) % SIZE == front) {
        cout << "Queue is Full!" << endl;
        return;
    }

    if (front == -1) {
        front = 0;
        rear = 0;
    } else {
        rear = (rear + 1) % SIZE;
    }

    queue[rear] = value;
}

// Display
void display() {
    if (front == -1) {
        cout << "Queue is Empty!" << endl;
        return;
    }

    cout << "Queue elements: ";
    int i = front;
    while (true) {
        cout << queue[i] << " ";
        if (i == rear)
            break;
        i = (i + 1) % SIZE;
    }
    cout << endl;
}


bool search(int value) {
    if (front == -1) return false;

    int i = front;
    while (true) {
        if (queue[i] == value)
            return true;
        if (i == rear)
            break;
        i = (i + 1) % SIZE;
    }
    return false;
}

void insertAtPosition(int value, int pos) {
    if (search(value)) {
        cout << value << " already exists in the queue." << endl;
        return;
    }

    if ((rear + 1) % SIZE == front) {
        cout << "Queue is Full! Cannot insert." << endl;
        return;
    }
    if (front == -1) {
        front = rear = 0;
        queue[0] = value;
        cout << value << " inserted at position 0" << endl;
        return;
    }
    int len = (rear >= front) ? rear - front + 1 : SIZE - front + rear + 1;
    if (pos < 0 || pos > len) {
        cout << "Invalid position!" << endl;
        return;
    }
    rear = (rear + 1) % SIZE;
    int i = rear;
    while (i != (front + pos) % SIZE) {
        int prev = (i - 1 + SIZE) % SIZE;
        queue[i] = queue[prev];
        i = prev;
    }
    queue[(front + pos) % SIZE] = value;
    cout << value << " inserted at position " << pos << endl;
}

int main() {
    enqueue(10);
    enqueue(20);
    enqueue(30);
    enqueue(40);

    display();

    insertAtPosition(25, 2); 
    display();

    insertAtPosition(20, 1); 
    display();

    return 0;
}
