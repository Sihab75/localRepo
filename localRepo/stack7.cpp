#include <iostream>
#include <string>
#include <vector>
using namespace std;

class {
    vector <int> stack;
    int top = -1;
public:
    void push (int val) {
        top++;
        stack.push_back (val);
    }
    void pop () {
        stack.pop_back ();
        top--;
    }
    void Top () {
        return stack [top];
    }
    bool empty () {
        return top < 0;
    }
};

int 