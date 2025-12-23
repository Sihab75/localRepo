#include <iostream>
#include <queue>
#include <vector>
#include <list>
using namespace std;

class Graph {
    int node;
    vector <list<int>> adj;
    bool dfs (int src, int pre, vector<bool>& vis) {
        vis[src] = true;
        for (int nigh: adj[src]) {
            if (!vis[nigh]) {
                if (dfs(nigh, src, vis)) {
                    return true;
                }
            } else if (pre != nigh) {
                return true;
            }
        }
        return false;
    }
public : 
    Graph (int n) {
        node = n;
        adj.resize (n);
    }
    void addEdges (int u, int v) {
        adj[u].push_back (v);
        adj[v].push_back (u);
    }

    void isCycle () {
        vector <bool> vis(node, false);
        if (dfs(0, -1, vis)) {
            cout << "Cycle is exist" << endl;
        } else {
            cout << " Cycle is not exist" << endl;
        }
    }
    void bfs (int src) {
        queue <int> q;
        vector <bool> vis(node, false);
        vector <int> pre(node, -1);
        vis[src] = true;
        q.push (src);
        while (!q.empty ()) {
            int nigh = q.front();
            q.pop ();
            for (int v : adj[nigh]) {
                if (!vis[v]) {
                    vis[v] = true;
                    pre[v] = nigh;
                    q.push (v);
                } else if (pre[nigh] != v) {
                    cout << "Cycle is Exist " << endl;
                    return;
                }
            }
        }
        cout << "Cycle is not Exist" << endl;
    }
};

int main () {
    int n;
    cout << "Enter the Number of vertex : ";
    cin >> n;
    Graph g (n);
    cout << "Enter the number of vertex : ";
    int e;
    cin >> e;
    while (e--) {
        cout << "Enter Edges of (u v) : " ;
        int u, v;
        cin >> u >> v;
        g.addEdges (u, v);
    }
    g.isCycle ();
    g.bfs (0);
    return 0;
}