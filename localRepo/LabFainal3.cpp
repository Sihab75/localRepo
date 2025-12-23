#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main () {
    vector <int> arr = {6, 7, 5, 4, 6 , 59, 19};
    int Max = INT_MIN;
    int secMax = INT_MIN;
    for (int i = 0; i < 7; i++) {
        if (Max < arr[i] || secMax < arr[i]) {
            if (Max < arr[i]) {
                secMax = Max;
                Max = arr[i];
            } else {
                secMax = arr[i];
            }
        }
    }
    cout << "second Large is : " << secMax << endl;
    return 0;
}