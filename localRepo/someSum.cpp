
#include <iostream>
using namespace std;

int sum(int n){
    int s = 0;
    while (n > 0) {

        s = s + n % 10;

        n /= 10;

    }

    return s;
}

int main () {
    int n,a,b;
    cin >> n >> a >> b;

    if (a > b) {
        swap(a,b);
    }
    int someSum = 0;
    for (int i = 1; i <= n; i++) {
        int s = sum(i);
        if (s >= a && s <= b) {

            someSum += i;
        }
    }

    cout << someSum << endl;

    return 0;

}
