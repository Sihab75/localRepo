#include <bits/stdc++.h>
#include <iostream>
#include <vector>
using namespace std;

int main () {
    vector <int> a;
    int n;
    cin >> n;
    for (int i = 0; i < n; i ++)  {
        int x;
        cin >> x;
        a.push_back(x);
    } 
    int Max = *max_element(a.begin(), a.end());
    int Min = *min_element(a.begin(), a.end());
    cout << Max << '\n' << Min << '\n';
    return 0; 
}
