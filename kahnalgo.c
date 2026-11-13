#include <stdio.h>
#define MAX 50

int adj[MAX][MAX];     /* adj[u][0..deg[u]-1] = neighbours of u (adjacency list) */
int deg[MAX];          /* number of neighbours of each vertex */
int indegree[MAX];

int main() {
    int V, E, i, u, v;
    int queue[MAX], front = 0, rear = 0;
    int result[MAX], count = 0;

    printf("Vertices: ");
    scanf("%d", &V);
    printf("Edges: ");
    scanf("%d", &E);
    printf("Enter edges (u v):\n");
    for (i = 0; i < E; i++) {
        scanf("%d %d", &u, &v);
        adj[u][deg[u]++] = v;     /* add v to u's list */
        indegree[v]++;
    }

    for (i = 0; i < V; i++)
        if (indegree[i] == 0)
            queue[rear++] = i;

    while (front < rear) {
        u = queue[front++];
        result[count++] = u;
        for (i = 0; i < deg[u]; i++) {
            v = adj[u][i];
            indegree[v]--;
            if (indegree[v] == 0)
                queue[rear++] = v;
        }
    }

    if (count != V) {
        printf("Cycle detected! Topological sort is not possible.\n");
    } else {
        printf("Topological Order:\n");
        for (i = 0; i < V; i++)
            printf("%d ", result[i]);
        printf("\n");
    }
    return 0;
}