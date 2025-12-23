#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <algorithm>
using namespace std;

class Graph{
    int node;
    vector <list<int>> adj;
public: 
    Graph (int n) {
        node = n;
        adj.resize (n);
    }
    void addEdges (int u, int v) {
        adj[u].push_back (v);
        adj[v].push_back (u);
    }
    int  bfs (int src, int dest) {
        vector <bool> vis(node, false);
        vector <int> pre(node, -1);
        vector <int> dis(node, -1);
        queue <int> q;
        vis[src] = true;
        dis[src] = 0;
        q.push (src);
        while (!q.empty()) {
            int nigh = q.front ();
            q.pop ();
            for (int v: adj[nigh]) {
                if (!vis[v]) {
                    pre[v] = nigh;
                    dis[v] = dis[nigh] + 1;
                    vis[v] = true;
                    q.push (v);
                }
            }
        }
        if (dis[dest] == -1) {
            return -1;
        }
        vector <int> path;
        for (int v = dest; v != -1; v = pre[v]) {
            path.push_back (v);
        }
        reverse (path.begin(), path.end());
        for (int v: path) {
            cout << v << "->";
        }
        return dis[dest];
    }
};

int main () {
    int n;
    cout << "Enter the Number of vertex : ";
    cin >> n;
    Graph g(n);
    cout << "Enter the number of Edges: ";
    int e;
    cin >> e;
    for (int i = 0; i < e; i++) {
        int u, v;
        cout << "Enter the Edges (u v) : ";
        cin >> u >> v;
        g.addEdges (u, v);
    }
    int src, dest;
    cout << "Enter  source and destination  : ";
    cin >> src >> dest;
    int distance = g.bfs (src, dest);
    cout << "Distance of " << src << " -> " << dest << " = " << distance << endl;
    return 0;
}