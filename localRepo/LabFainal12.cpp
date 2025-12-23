#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Graph {
    int node;
    vector <vector<int>> adj;
public:
    Graph (int n) {
        node = n;
        adj.resize(n, vector <int> (n, 0));
    }
    void addEdges (int u, int v) {
        adj[u][v] ++;
        adj[v][u]++;
    }
    int countEdges () {
        int count = 0; 
        for (int i = 0; i  < node; i++) {
            for (int j = i + 1; j < node; j++) {
                if (adj[i][j] != 0 ) {
                    count++;
                }
            }
        }
        return count;
    }
    void checkBSTraversal (int src) {
        vector <bool> vis (node, false);
        queue <int> q;
        vis[src] = true;
        q.push (src);
        while (!q.empty ()) {
            int u = q.front ();
            q.pop();
            for (int i = 0; i < node; i++) {
                if (adj[u][i] != 0 && !vis[i]) {
                    vis[i] = true;
                    q.push (i);
                }
            }
        }

        for (bool found : vis) {
            if (!found) {
                cout << "Not connected " << endl;
                return;
            }
        }
        cout << "connected" << endl;
    }
};

int main () {
    Graph g(n)
}