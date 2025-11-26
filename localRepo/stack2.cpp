#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Stack {
    vector <int> stack;
    int top = -1;
public:
    void push (int val) {
        top++;
        stack.push_back (val);
    }
    int Top () {
        return stack[top];
    }
    int pop () {
        int val = stack [top];
        stack.pop_back ();
        top--;
        return val;
    }

    void print () {
        for (int i = top; i >= 0; i--) {
            cout << stack[i] << ' ';
        }
        cout << endl;
    }
    bool empty () {
        return top < 0;
    }
};

int main () {
    Stack s;
    int n;
    if (s.empty()) {
        cout << "Stack is empty" << endl;
    }
    cout << "Enter the Number of element is : ";
    cin >> n;
    cout << "Enter elements is : ";
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        s.push (x);
    }
    s.print ();
    int val = s.pop ();
    s.print ();
    cout << "Top element is : " << s.Top () << endl;
    val = s.pop ();
    int val1 =s.pop ();
    s.push (val + val1);
    s.print ();
    int choice;
    do {
        cout << "1. sum\n2.sub\n3.mul\n4.div\n5.Exit\nEnter choice is: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            val = s.pop ();
            val1 = s.pop ();
            s.push (val + val1);
            s.print();
            break;
        case 2:
            val = s.pop ();
            val1 = s.pop ();
            s.push (val - val1);
            s.print();
            break;
        case 3:
            val = s.pop ();
            val1 = s.pop ();
            s.push (val *val1);
            s.print();
            break;
        case 4:
            val = s.pop ();
            val1 = s.pop ();
            s.push (val/val1);
            s.print();
            break;
        case 5:
            break;
        default :
            cout << "wrong choice!";
        break;
        }
    } while (choice != 5);
    s.print ();
    return 0;
}