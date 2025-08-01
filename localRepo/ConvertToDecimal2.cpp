#include <iostream>
using namespace std;

int bainary (int n){
    int pow = 1, remainder,bi = 0;
    while (n > 0) {
        remainder = n % 2;
        if(remainder) {
            bi = bi + remainder * pow;
            pow *= 10;
        }
        n /= 2;
    }

    return bi;
}
int decimal (int n) {
    int bi = bainary(n);
    int pow =1,di = 0,rem;
     while (bi > 0) {
        rem = bi % 10;
        di = di + rem * pow;
        pow *= 2;
        bi /= 10;
     }

     return di;
}

int main (){
  int n;
  cin >> n;

  for (int i = 1; i <= n; i++){
    int t;
    cin >> t;

    int di = decimal(t);

    cout << di << endl;

  }

  return 0;

}
