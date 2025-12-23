#include <iostream>
using namespace std;

class Stack {
    int stack [100];
    int n = 100;
    int top = -1;
public :
    void push (int val) {
        if (top == n - 1) {
            cout << "Stack is full!" << endl;
            return;
        }
        stack[++top] = val;
    }

    void pop () {
        if (top == -1) {
            cout << "Stack is empty!" << endl;
            return;
        }
        top--;
    }
    int Top () {
        if (top == -1){
            cout << "Stack is Empty !";
            return -1;
        }
        return stack[top];
    }
    bool empty () {
        return top == -1;
    }

    void display () {
        for (int i = top; i >= 0; i--) {
            cout << stack[i] << ' ';
        }
        cout << endl;
    } 

};

int main () {
    Stack s;
    s.push (20);
    s.push (18);
    s.push (90);
    s.push (58);
    s.push (240);
    s.push (318);
    s.push (201);
    s.push (9);
    s.display ();
    s.pop ();
    s.display ();
    cout << s.Top () << endl;
    return 0;
}