#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while(t--){
        int n; cin >> n;
        vector<int> a(n);
        for(int i=0;i<n;i++) cin >> a[i];

        vector<int> dp(n+1, 1e7);
        dp[0] = 0;

        for(int v : a){
            for(int x = v; x <= n; x++){
                if(x % v == 0){ 
                    dp[x] = min(dp[x],dp[x/v] + 1);
                }
            }
        }

        for(int i=1;i<=n;i++){
            cout << (dp[i] == 1e7 ? -1 : dp[i]) << " ";
        }
        cout << "\n";
    }
    return 0;
}



