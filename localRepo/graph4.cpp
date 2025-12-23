#include <iostream>
#include <vector>
#include <list>
#include <queue>
using namespace std;

class Graph {
    int node;
    vector<list<int>> adj;
    void dfsHelper (int src, vector<bool>& vis) {
        vis[src] = true;
        for (int nigh: adj[src])
            if (!vis[src]) 
                dfsHelper (nigh, vis);
    }
public:
    Graph (int n) {
        node = n;
        adj.resize (n);
    }
    void addEdges (int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void bfs (int src) {
        vector <bool> vis(node, false);
        queue <int> q;
        vis[src] = true;
        q.push (src);
        while (!q.empty()) {
            int n = q.front ();
            q.pop();
            for (int nigh: adj[n]) {
                if (!vis[nigh]){
                    vis[nigh] = true;
                    q.push(nigh);
                }
            }
        }
        int count = 0;
        for (bool found : vis) {
            if (!found) {
                count++;
            }
        }
        cout << "Connected components = " << count << endl; 
    }

    void dfs (int src) {
        vector <bool> vis (node, false);
        dfsHelper (src, vis);
        int count = 0;
        for (bool found: vis) {
            if (!found) {
                count ++;
            }
        }
        cout << "Connected components : " << count << endl;
    }
};

int main () {
    int n;
    cout << "Enter the Number of Vertex :";
    cin >> n;
    Graph g(n);
    cout << "Enter the Number of Edges : ";
    int e;
    cin >> e;
    while (e--) {
        int u, v;
        cout << "Enter Edges (u, v) : ";
        cin >> u >> v;
        g.addEdges (u, v);
    }

    g.bfs (0);
    g.dfs (0);
    return 0;
}