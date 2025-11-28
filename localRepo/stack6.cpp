#include <iostream>
#include <vector>
#include <string>
#include <cctype>
using namespace std;

class Stack {
    vector <int> stack;
    int top = -1;
public:
    void push (int val) {
        top++;
        stack.push_back (val);
    }
    void pop () {
        stack.pop_back();
        top--;
    }
    int Top () {
        return stack[top];
    }
    bool empty () {
        return top < 0;
    }
};

int main () {
    Stack s;
    string str;
    getline(cin, str);
    for (char ch: str) {
        if (ch == ' ') {
            continue;
        }
        if (isdigit (ch)) {
            s.push (ch - '0');
        } else {
            int val2 = s.Top ();
            s.pop ();
            int val1 = s.Top ();
            s.pop ();
            switch (ch) {
                case '+' : s.push (val1 + val2); break;
                case '-' : s.push (val1 - val2); break;
                case '*' : s.push (val1 * val2); break;
                case '/' : s.push (val1 / val2); break;
                default : break;
            }
        }
    }
    cout << s.Top () << endl;
    return 0;
}