#include <iostream>
using namespace std;

int main () {
    int n;
    cin >> n;

    int first = 0,second = 1;
    for(int i = 1; i <= n; i++){

       cout << first << " ";
       int fib = first + second;
       first = second;
       second = fib;
    }
   return 0;
}
