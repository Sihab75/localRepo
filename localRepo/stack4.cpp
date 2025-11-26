#include <iostream>
#include <string>
#include <stack>
using namespace std;

int main () {
    stack <char> s;
    cout << "enter string is: ";
    string str;
    getline(cin, str);
    for (int i = 0; i < str.size(); i++) {
        s.push (str[i]);
    }
    int i = 0;
    while (!s.empty()) {
        str[i] = s.top();
        i++;
        s.pop ();
    }
    cout << str;
    cout << endl;
    return 0;
}