#include <iostream>
#include <vector>
#include <queue>
#include <list>
using namespace std;

class Graph {
    int V;
    vector <list <int>> adj;
    void dfsHelper (int src, vector<bool>& vis) {
        vis[src] = true;
        for (int nigh: adj[src]) {
            if (!vis[nigh]) {
                dfsHelper (nigh, vis);
            }
        }
    }
public:
    Graph (int v) : V(v), adj(v) { } 
    void addEdges (int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    bool dfs (int src) {
        vector <bool> vis(V, false);
        dfsHelper (src, vis);
        for (bool found: vis) {
            if (!found) {
                return false;
            }
        }
        return true;
    }
    bool bfs (int src) {
        queue <int> q;
        vector <bool> vis (V, false);
        vis[src] = true;
        q.push(src);
        while (!q.empty()) {
            int node = q.front ();
            q.pop ();
            for (int nigh: adj[node]) {
                if (!vis[nigh]) {
                    vis[nigh] = true;
                    q.push(nigh);
                }
            }
        }
        for (bool found: vis) {
            if (!found) {
                return false;
            }
        }
        return true;
    }
};

int main () {
    int v;
    cout << "Enter the Number of Vertex : ";
    cin >> v;
    Graph g(v);
    cout << "Enter the Number of Edges : ";
    int e;
    cin >> e;
    for (int i = 0; i < e; i++) {
        cout << "Enter the Edges (u v) : ";
        int u, v;
        cin >> u >> v;
        g.addEdges (u, v);
    }
    if (g.bfs(0) && g.dfs(0)) {
        cout << "The graph is connected " << endl;
    } else {
        cout << "The graph is not connected " << endl;
    }
    return 0;
}