#include <iostream>
#include <vector>
using namespace std;

class Queue {
    vector <int> queue;
    int front = -1;
    int rear = -1;
public : 
    void enqueue (int val) {
        if (front == -1) {
            front = 1;
        }
        rear++;
        queue.push_back(val);
    }

    int dequeue () {
        if (rear == -1) {
            return - 1;
        }
        int val = queue.front ();
        queue.erase (queue.begin());
        rear--;
        if (queue.empty()) {
            front = -1;
        }
        return val;
    }

    void display () {
        for (int val: queue) {
            cout << val << " ";
        }
        cout << endl;
    }
};

int main () {
    Queue q;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        q.enqueue (x);
    }
    q.display ();
    q.dequeue ();
    q.display ();
    return 0;
}