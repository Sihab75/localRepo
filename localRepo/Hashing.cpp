#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < b; i++)
#define endl '\n'
#define ll long long
#define vi vector<int>
#define n 10
#define pb(x) push_back (x)
int h[n];

void insert (int val) {
    int i = val % n;
    while (h[i] != -1) i = (i+1)%n;
    h[i] = val;
}

int search (int val) {
    int i = val % n;
    int j = 0;
    while (h[i] != -1 && j < n) {
        if (h[i] == val) return i;
        i = (i + 1) % n;
        j++;
    }
    return -1;
}

int main () {
    rep (i, 0, n) h[i] = -1;
    cout << "Enter the Number of Insert value : ";
    int m;
    cin >> m;
    cout << "Enter the Insert value : ";
    int val;
    rep (i,0, m){ 
        cin >> val;
        insert (val); 
    }
    cout << "Display the Hash Table : ";
    rep (i,0,n) cout << h[i] << ' ';
    cout << endl;
    cin >> val;
    cout << (search (val) != -1? "found" : "Not found") << endl;
    return 0;
}