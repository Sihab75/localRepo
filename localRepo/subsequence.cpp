#include <bits/stdc++.h>
using namespace std;
#define endl '\n';

int main () {
    int a, b;
    cin >> a >> b;
    int arr1[a];
    int arr2[b];
    for (int i = 0; i < a; i++) {
        cin >> arr1[i];
    }
    for (int i = 0; i  < b; i++) {
        cin >> arr2[i];
    }
    int i = 0;
    int j = 0;
    while (i < a && j < b) {
        if (arr1[i] == arr2[j]) {
            j++;
        }
        i++;
    }
    if (j == b) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
    return 0;
}