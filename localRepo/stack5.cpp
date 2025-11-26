#include <iostream>
#include <stack>
#include <string>
using namespace std;

bool check (string str) {
    stack <char> s;
    for (char ch: str) {
        if (ch == '[' || ch == '{' || ch == '(') {
            s.push (ch);
        } else if (ch == ')' || ch == ']' || ch == '}'){
            if (s.empty()) {
                return false;
            }
            if ((ch == '}' && s.top() != '{') || (ch == ']'&& s.top() != '[') || (ch == ')' && s.top() != '(')) {
                return false;
            }
            s.pop();
        }
    }
    return true;
}

int main () {
    string str;
    cout << "enter parentheses is : ";
    getline (cin, str);
    if (check(str)) {
        cout << "your parentheses are balanced" << endl;
    } else {
        cout << "your parentheses are not balanced" << endl;
    }
    return 0;

}