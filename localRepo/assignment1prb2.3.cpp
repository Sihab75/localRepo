#include <iostream>

using namespace std;

int main () {

    for(int row = 1 ; row <= 4 ; row ++) {

        for (int space = 4 - row ; space >= 1 ; space --) {

            cout << "  ";

        }

        int digit = 1;

        for (int col = 1 ; col <= row ; col ++) {

            cout << digit << "   ";

            digit = digit * (row - col) / col;

        }

        cout << endl;
    }

    return 0;

}
