#include <stdio.h>
#define MAX 50

int adj[MAX][MAX];
int deg[MAX];
int visited[MAX], recStack[MAX];

int dfs(int u) {
    int i, v;
    visited[u] = 1;
    recStack[u] = 1;
    for (i = 0; i < deg[u]; i++) {
        v = adj[u][i];
        if (!visited[v]) {
            if (dfs(v)) return 1;
        } else if (recStack[v]) {
            return 1;                /* back-edge found */
        }
    }
    recStack[u] = 0;                 /* leaving this vertex */
    return 0;
}

int main() {
    int V, E, i, u, v, found = 0;

    printf("Vertices: ");
    scanf("%d", &V);
    printf("Edges: ");
    scanf("%d", &E);
    printf("Enter edges (u v):\n");
    for (i = 0; i < E; i++) {
        scanf("%d %d", &u, &v);
        adj[u][deg[u]++] = v;
    }

    for (i = 0; i < V; i++) {
        if (!visited[i] && dfs(i)) {
            found = 1;
            break;
        }
    }

    if (found)
        printf("Cycle detected in the directed graph.\n");
    else
        printf("No cycle found in the directed graph.\n");
    return 0;
}