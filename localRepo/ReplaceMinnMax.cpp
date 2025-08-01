#include <iostream>
#include <limits.h>
using namespace std;

int main () {
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    int mx = INT_MIN;
    int mn = INT_MAX;
    int mxi,mni;
    for (int i = 0;i < n; i++){
        if(mx < a[i]){
            mx = max(mx,a[i]);
            mxi = i;
        }
        if (mn > a[i]){
            mn = min(mn,a[i]);
            mni = i;
        }
    }
    swap(a[mxi],a[mni]);
    for (int i = 0; i < n; i++){
        cout << a[i] << ' ';
    }
    cout << '\n';
    return 0;
}