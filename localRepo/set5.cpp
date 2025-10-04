#include <bits/stdc++.h>
using namespace std;

int main () {
    int n;
    cin >> n;
    set <int> s1;
    set <int> s2;
    set <int> unions;
    set <int> intersections;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        s1.insert(a);
    }
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        s2.insert(a);
    }
    for (set <int> :: iterator it = s1.begin(); it != s1.end(); it++) {
        unions.insert(*it);
    }
    for (set <int> :: iterator it = s2.begin(); it != s2.end(); it++) {
        unions.insert(*it);
    }
    for (set <int> :: iterator it = s1.begin(); it != s1.end(); it++) {
        if (s2.find(*it) != s2.end()) {
            intersections.insert(*it);
        } 
    }
    cout << "union = " ;
    for (set <int> :: iterator it = unions.begin(); it != unions.end(); it++) {
        cout << *it << ' ';
    }
    cout << endl << "intersections == ";
    for (set <int> :: iterator it = intersections.begin(); it != intersections.end();it++) {
        cout << *it << ' ';
    }
    cout << endl;
    return 0;
}