#include <iostream>
#include <stack>
using namespace std;

class Queue{
    stack <int> s1, s2;
public :
    void enqueue (int val) {
        s1.push (val);
    }
    void dequeue () {
        if (s1.empty () && s2.empty ()) {
            cout << "stack already empty" << endl;
            return 0;
        }
        if (s2.empty()) {
            while (!s1.empty) {
                s2.push(s1.top ());
                s1.pop();
            }
        }
        s2.pop ();
    }
    
}