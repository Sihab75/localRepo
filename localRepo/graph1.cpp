#include <iostream>
#include <queue>
using namespace std;

class Graph {
    int node;
    vector <vector<int>> adj;
    void dfsHelper (int src, vector<bool>& vis) {
        cout << src << ' ';
        vis[src] = true;
        for (int i = 0; i < node; i++) {
            if (adj[src][i] != 0 && !vis[i]) {
                dfsHelper(i, vis);
            }
        }
    }

public:
    Graph (int n) {
        node = n;
        adj.resize(n,vector<int> (n, 0));
    }
    void addEdges (int u, int v) {
        adj[u][v]++;
        adj[v][u]++;
    }
    void display () {
        cout << "Adjacency Matrix :" << endl;
        for (int i = 0; i < node; i++) {
            for (int j = 0; j < node; j++) {
                cout << adj[i][j] << ' ';
            }
            cout << endl;
        }
    }
    void bfs (int src) {
        queue <int> q;
        vector <bool> vis(node, false);
        vis[src] = true;
        q.push(src);
        while (!q.empty()) {
            int n = q.front ();
            q.pop();
            cout << n << ' ';
            for (int i = 0; i < node; i++) {
                if (adj[n][i] != 0 && !vis[i]) {
                    vis[i] = true;
                    q.push(i);
                }
            }
        }
        cout << endl;
    } 
    
    void dfs (int src) {
        vector <bool> vis (node, false);
        dfsHelper (src, vis);
        cout << endl;
    }
};

int main () {
    int n;
    cout << "Enter the number of node : ";
    cin >> n;
    Graph g(n);
    g.display ();
    cout << "Enter the number of Edges: ";
    int e;
    cin >> e;
    for (int i = 0; i < e; i++) {
        int u, v;
        cout << "Enter the Edges (u v) : ";
        cin >> u >> v;
        g.addEdges (u, v);
    }
    g.display ();
    int src;
    cout << endl << "enter the src node : ";
    cin >> src;
    g.bfs (src);
    g.dfs (src);
    return 0;
}

