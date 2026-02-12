#include <iostream>
#include<vector>
//#include<unordered_map>
#include <map>
#include<string>

using namespace std;

#define fixed(n) fixed << setprecision(n)
#define ceil(n, m) (((n) + (m) - 1) / (m))
#define add_mod(a, b, m) (((a % m) + (b % m)) % m)
#define sub_mod(a, b, m) (((a % m) - (b % m) + m) % m)
#define mul_mod(a, b, m) (((a % m) * (b % m)) % m)
#define all(vec) vec.begin(), vec.end()
#define rall(vec) vec.rbegin(), vec.rend()
#define sz(x) int(x.size())
#define debug(x) cout << #x << ": " << (x) << "\n";
#define fi first
#define se second
#define ll long long
#define ull unsigned long long
#define EPS 1e-9
#define PI acos(-1)
#define rep(i,a,b) for(int i = a; i < b; i++)
#define ump unordered_map
#define mp map
#define endl '\n'
void Solve(){
    int n;
    cin>>n;
    cin.ignore();
    mp<string,string>dol;
    mp<string,int>vot;
    string name,dolName;
    rep(i,0,n){
        getline(cin, name);
        getline(cin, dolName);
        dol[name]=dolName;
        vot[name]=0;
    }
    int m;
    cin>>m;
    cin.ignore();
    rep(i,0,m){
        getline(cin,name);
        if(vot.count(name)){
            vot[name]++;
        }
    }
    int mx=-1;
    string ans;
    bool tie=false;
    for (map<string,int>::iterator it = vot.begin(); it!=vot.end();it++) {
        if (it->se > mx) {
            mx = it->se;
            ans = it->first;
            tie = false;
        } 
        else if (it->se == mx) {
            tie = true;
        }
    }
        if (tie) {
            cout << "tie\n";
        } else {
            cout<< ((dol[ans] != "independent")?dol[ans]:"independent")<<endl;
        }
}

int main(){
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int test_cases = 1;
    cin >> test_cases;
    cin.ignore();
    for(int tc = 1; tc <= test_cases; tc++){
        // cout << "Case #" << tc << ": ";
        Solve();
    }
    return 0;
}