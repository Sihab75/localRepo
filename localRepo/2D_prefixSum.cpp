#include <iostream>
#include <vector>
using namespace std;
int main () {
    int n,m;
    cin >> n >> m;
    vector<vector<int>> matrix(n,vector<int>(m));
    for(int i =0;i<n;i++)
        for(int j=0;j<m;j++)
            cin>> matrix[i][j];
    vector<vector<int>> pre(n+1,vector<int>(m+1,0));
    for(int i = 1;i <= n;i++)
        for(int j=1;j<=m;j++) 
            pre[i][j]= matrix[i-1][j-1]+pre[i][j-1]-pre[i-1][j-1] + pre[i-1][j];

    for(int i = 1;i <=n;i++){
        for(int j = 1;j<=m;j++)
            cout<<pre[i][j]<<' ';
        cout <<endl;
    }
    return 0;
}