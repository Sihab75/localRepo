#include <iostream>
#include <vector>
using namespace std;

class Graph {
    int node;
    vector<vector<int>> adj;
public: 
    Graph (int n) {
        node= n;
        adj.resize (n, vector<int> (n, 0));
    }
    void addEdge (int u, int v) {
        adj[u][v]++;
        adj[v][u]++;
    }
    void display () {
        cout << endl << "Adjacency Matrix:" << endl;
        for (int i = 0; i< node; i++) {
            for (int j = 0; j < node; j++) {
                cout << adj[i][j] << ' ';
            }
            cout << endl;
        }
    }
    void findPropertic () {
        int multiEdges = 0;
        int loop = 0;
        for (int i = 0; i < node; i++) {
            int degree = 0;
            for (int j = 0; j < node; j++) {
                if (i==j && adj[i][j] > 0) {
                    loop += adj[i][j];
                    degree += 2 * adj[i][j];
                } else {
                    degree += adj[i][j];
                }

                if (i < j && adj[i][j] > 1) {
                    multiEdges += (adj[i][j] - 1);
                }
            }
            cout << "Node " << i << " : Degree = " << degree << endl;
        }
        cout << "Total Loops = " << loop << endl;
        cout << "Total Multi-Edges = " << multiEdges << endl;
    }
};

int main () {
    int n;
    cout << "enter the number of node: ";
    cin >> n;
    Graph g(n);
    g.display ();
    int e;
    cout << "Enter number of edges : ";
    cin >> e;
    cout << "Enter edges (u v) : " << endl;
    for (int i = 0; i < e; i++) {
        int u, v;
        cin >> u >> v;
        g.addEdge (u, v);
    }
    g.display ();
    g.findPropertic ();
    return 0;
}