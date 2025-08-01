#include <iostream>
#include<limits.h>
#include <algorithm>
using namespace std;

int main () {
    int n;
    cin >> n;
    int a[n];
    int mi = INT_MAX;
    for (int i = 0; i < n; i++){
        cin >> a[i];
        mi = min(mi, a[i]);
    }
    int count = 0;
    for (int i = 0; i < n; i++){
        if (mi == a[i]){
            count ++;
        }
    }
    if (count % 2 != 0) {
        cout << "Lucky" << '\n';
    } else {
        cout << "Unlucky" << '\n';
    }
    return 0;

}