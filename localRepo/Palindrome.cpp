#include <iostream>

using namespace std;

int main () {

    int num;

    cin >> num;

    int remainder,revers = 0;
    int temp = num;
    while (temp >= 1) {

        remainder = temp % 10;
        revers = revers * 10 + remainder;
        temp /= 10;

    }

    cout << revers << endl;

    if (num == revers) {

        cout << "YES" <<endl;

    } else {

        cout << "NO" <<endl;
    }

    return 0;

}
