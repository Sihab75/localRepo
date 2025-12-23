#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Graph {
    int node;
    vector<vector <int>> adj;
    void dfsHelper (int src, vector <int>& vis) {
        cout << src << ' ';
        vis[src] = true;
        for (int nigh: adj[src]) {
            if (!vis[nigh]) {
                dfsHelper (nigh, vis);
            }
        }
    }
public:
    Graph(int n) {
        node = n;
        adj.resize (n);
    }
    void addEdges (int u, int v) {
        adj[u].push_back (v);
        adj[v].push_back (u);
    }
    void print () {
        for (int i = 0; i < node; i++) {
            cout << i << ':';
            for (int nigh: adj[i]) {
                cout << nigh << ' ';
            }
            cout << endl;
        }
    }
    void bfs (int src) {
        queue <int> q;
        vector <bool> vis (node, false);
        q.push(src);
        vis[src] = true;
        while (!q.empty()) {
            int v = q.front ();
            q.pop();
            cout << v << ' ';
            for (int nigh: adj[v]) {
                if (!vis[nigh]) {
                    vis[nigh] = true;
                    q.push (nigh);
                }
            }
        }
        cout << endl;
    }
    void dfs (int src) {
        vector <int> vis (node);
        dfsHelper (src, vis);
        cout << endl;
    }
};

int main () {
    int n;
    cout << "Enter the Number of vertex : ";
    cin >> n;
    Graph g(n);
    cout << "Enter the Number of edges : ";
    int e;
    cin >> e;
    for (int i = 0; i < e; i++) {
        int u, v;
        cout << "Enter the Edges (u v) : ";
        cin >> u >> v;
        g.addEdges (u, v);
    }
    g.print();
    g.bfs (0);
    g.dfs (0);
    return 0;
}