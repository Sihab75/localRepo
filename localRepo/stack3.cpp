#include <iostream>
#include <vector>
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
        return top;
    }
    int pop () {
        int val = stack[top];
        stack.pop_back();
        top--;
        return val;
    }
    bool empty () {
        return top < 0;
    }
    void delete_From_item (int item) {
        Stack temp;
        while (!empty()) {
            if (stack[top] == item) {
                pop ();
                break;
            }
            temp.push (stack[top]);
            pop ();
        }
        while (!temp.empty()) {
            push(temp.pop ());
        }
    }
    void print () {
        for (int i = top; i>=0; i--) {
            cout << stack[i] << ' ';
        }
        cout << endl;
    }
};

int main () {
    Stack s;
    cout << "Enter the Number of Element is : ";
    int n;
    cin >> n;
    cout << "enter element is : ";
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        s.push (x);
    }
    s.print ();
    cout << "Enter your item is : ";
    int x;
    cin >> x; 
    s.delete_From_item (x);
    s.print ();
    return 0;
}