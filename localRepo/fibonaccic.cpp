#include <iostream>
using namespace std;

int main () {
    int n;
    cin >> n;
    long long first = 0,second = 1;
    for (int i = 1; i < n; i++){
        long long next = first + second;
        first = second;
        second = next;
    }
    cout << first << '\n';
    return 0;
}