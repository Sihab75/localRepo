#include <stdio.h>

void dfs (int src, int vis[], int node, int matrix [][node]) {
    vis[src] = 1;
    printf("%d ", src);
    for (int i = 0; i < node; i++) {
        if (matrix[src][i] >= 1 && vis[i] != 1) {
            dfs (i, vis, node, matrix);
        }
    }
}

int main () {
    int node;
    printf("Enter the number of vertex : ");
    scanf("%d", &node);
    int matrix[node][node];
    for (int i = 0; i < node; i++) {
        for (int j = 0; j < node; j++) {
            matrix [i][j] = 0; 
        }
    }
    int e;
    printf("enter the number of Edges : ");
    scanf ("%d", &e);
    for (int i = 0; i < e; i++) {
        int u, v;
        printf("Enter Edges of (u v) : ");
        scanf ("%d %d", &u, &v);
        matrix[u][v]++;
        matrix[v][u]++;
    }
    printf ("Adjacency Matrix \n");
    for (int i = 0; i < node; i++) {
        for (int j = 0; j < node; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf ("DFS Traversal\n");
    int src;
    printf("Enter the source is : ");
    scanf ("%d", &src);
    int vis[node];
    for (int i = 0; i < node; i++) {
        vis[i] = 0;
    } 
    dfs (src, vis, node, matrix);
    printf("\n");
    return 0;
}