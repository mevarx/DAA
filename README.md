# CSE 204 – DAA End-Sem Lab: Study Guide (C)

**Exam format:** 1 hour, 50 marks, ONE random question out of 5.
Paper: pseudocode (20) + complexity (5). Computer: program (15) + output (10).

## 1-Hour Game Plan

| Time | What to do |
|------|-----------|
| 0–15 min | Write algorithm + pseudocode + complexity on paper (25 marks done) |
| 15–45 min | Type the C program, compile, fix errors |
| 45–55 min | Run sample + additional test case, show output |
| 55–60 min | Be ready for viva questions |

**Compile and run:**
```
gcc program.c -o program
./program          (Linux/Mac)      program.exe   (Windows)
```

**Golden rules:** keep the code short, use fixed-size arrays (`#define MAX 100`), no fancy features. Type the sample input exactly as given.

---

# Q1. Bucket Sort (Exp 3)

### Idea (say this in viva)
Numbers are in [0,1). Make `n` buckets. Put each number in bucket `int(n * x)`. Sort each bucket (insertion sort). Join buckets in order.

### Pseudocode
```
BucketSort(arr, n):
    create n empty buckets
    for i = 0 to n-1:
        idx = floor(n * arr[i])
        insert arr[i] into bucket[idx]
    for i = 0 to n-1:
        sort bucket[i]
    k = 0
    for i = 0 to n-1:
        for each element x in bucket[i]:
            arr[k++] = x
    return arr
```

### C Code
```c
#include <stdio.h>
#define MAX 100

void insertionSort(float a[], int n) {
    for (int i = 1; i < n; i++) {
        float key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

int main() {
    int n, i, j, k = 0;
    float arr[MAX], bucket[MAX][MAX];
    int count[MAX] = {0};          

    printf("Enter number of elements: ");
    scanf("%d", &n);
    printf("Enter elements:\n");
    for (i = 0; i < n; i++)
        scanf("%f", &arr[i]);

    printf("Original Array:\n");
    for (i = 0; i < n; i++)
        printf("%.2f ", arr[i]);

    for (i = 0; i < n; i++) {
        int idx = (int)(n * arr[i]);
        bucket[idx][count[idx]] = arr[i];
        count[idx]++;
    }

    for (i = 0; i < n; i++)
        insertionSort(bucket[i], count[i]);

    for (i = 0; i < n; i++)
        for (j = 0; j < count[i]; j++)
            arr[k++] = bucket[i][j];

    printf("\nSorted Array:\n");
    for (i = 0; i < n; i++)
        printf("%.2f ", arr[i]);
    printf("\n");
    return 0;
}
```

### Test
```
6
0.42 0.32 0.23 0.52 0.25 0.47      ->  0.23 0.25 0.32 0.42 0.47 0.52
5
0.12 0.89 0.45 0.67 0.21           ->  0.12 0.21 0.45 0.67 0.89
```

### Complexity
- Best: **O(n + k)** (uniform data, ~1 element per bucket)
- Average: **O(n + k)**
- Worst: **O(n²)** (all elements land in one bucket, insertion sort)
- Space: **O(n + k)** (k = number of buckets)

### Viva
- *Why [0,1)?* Because `n*x` must give an index from 0 to n-1. If x = 1.0 the index would be n (out of range).
- *Is it stable?* Yes, if the inner sort is stable (insertion sort is).
- *When is it good?* Uniformly distributed data.

---

# Q2. Fractional Knapsack (Exp 6)

### Idea
Greedy: compute profit/weight for every item, sort descending, take whole items while they fit, then take a **fraction** of the next item to fill the bag.

### Pseudocode
```
FractionalKnapsack(items, n, W):
    for each item i:
        ratio[i] = profit[i] / weight[i]
    sort items in descending order of ratio
    remaining = W
    totalProfit = 0
    for i = 1 to n:
        if remaining == 0: break
        if weight[i] <= remaining:
            take whole item
            remaining = remaining - weight[i]
            totalProfit = totalProfit + profit[i]
        else:
            fraction = remaining / weight[i]
            totalProfit = totalProfit + profit[i] * fraction
            remaining = 0
    return totalProfit
```

### C Code
```c
#include <stdio.h>
#define MAX 50

int main() {
    int n, i, j, id[MAX];
    float W, w[MAX], p[MAX], r[MAX];
    float remaining, totalProfit = 0, t;
    int ti;

    printf("Enter number of items: ");
    scanf("%d", &n);
    printf("Enter capacity: ");
    scanf("%f", &W);
    for (i = 0; i < n; i++) {
        printf("Item %d: Weight and Profit: ", i + 1);
        scanf("%f %f", &w[i], &p[i]);
        r[i] = p[i] / w[i];
        id[i] = i + 1;
    }

    printf("Ratios: ");
    for (i = 0; i < n; i++)
        printf("I%d=%.2f ", id[i], r[i]);
    printf("\n");

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (r[j] < r[j + 1]) {
                t = r[j]; r[j] = r[j + 1]; r[j + 1] = t;
                t = w[j]; w[j] = w[j + 1]; w[j + 1] = t;
                t = p[j]; p[j] = p[j + 1]; p[j + 1] = t;
                ti = id[j]; id[j] = id[j + 1]; id[j + 1] = ti;
            }
        }
    }

    remaining = W;
    for (i = 0; i < n && remaining > 0; i++) {
        if (w[i] <= remaining) {
            printf("I%d: %.0f kg (100%%)\n", id[i], w[i]);
            remaining -= w[i];
            totalProfit += p[i];
        } else {
            float frac = remaining / w[i];
            printf("I%d: %.0f kg (%.2f%%)\n", id[i], remaining, frac * 100);
            totalProfit += p[i] * frac;
            remaining = 0;
        }
    }

    printf("Total Weight = %.0f kg\n", W - remaining);
    printf("Max Profit = %.2f\n", totalProfit);
    return 0;
}
```

### Test
```
3
50
10 60
20 100
30 120
-> I1: 10 kg (100%), I2: 20 kg (100%), I3: 20 kg (66.67%), Max Profit = 240

4
60
10 100
20 120
30 120
40 160
-> ratios 10, 6, 4, 4 -> Max Profit = 340
```

### Complexity
- **O(n log n)** with a good sort (the sort dominates; the greedy loop is O(n)).
- My bubble sort is O(n²). It is fine to type for the exam, but **write O(n log n) on paper** and say "with a faster sort like merge sort / qsort".
- Space: O(n)

### Viva
- *0/1 vs Fractional?* In 0/1 you take the whole item or nothing (needs DP). In Fractional you can take part of an item, so greedy gives the optimal answer.
- *Why does greedy work here?* Taking the best ratio first never wastes capacity.

---

# Q3. Huffman Coding (Exp 8)

### Idea
Make a leaf for each character. Repeatedly take the **two smallest-frequency nodes**, merge them into a parent (freq = sum), put the parent back. When one node is left, it is the root. Walk the tree: left = 0, right = 1.

Rule that matches the expected output: the **first minimum is the left child**, the second minimum is the right child.

### Pseudocode
```
Huffman(chars, freq, n):
    create a leaf node for every character
    nodes = list of these n nodes
    while size(nodes) > 1:
        a = remove node with smallest freq
        b = remove node with next smallest freq
        parent = new node(freq = a.freq + b.freq)
        parent.left  = a
        parent.right = b
        insert parent into nodes
    root = the only node left
    GenerateCodes(root, "")

GenerateCodes(node, code):
    if node is a leaf:
        print node.char, code
        return
    GenerateCodes(node.left,  code + "0")
    GenerateCodes(node.right, code + "1")
```

### C Code
```c
#include <stdio.h>
#include <stdlib.h>
#define MAX 50

struct Node {
    char ch;
    int freq;
    struct Node *left, *right;
};

struct Node* newNode(char ch, int freq) {
    struct Node* n = (struct Node*)malloc(sizeof(struct Node));
    n->ch = ch;
    n->freq = freq;
    n->left = n->right = NULL;
    return n;
}

void printCodes(struct Node* root, char code[], int depth) {
    if (root->left == NULL && root->right == NULL) {  
        code[depth] = '\0';
        printf("%c      %s\n", root->ch, code);
        return;
    }
    code[depth] = '0';
    printCodes(root->left, code, depth + 1);
    code[depth] = '1';
    printCodes(root->right, code, depth + 1);
}

int main() {
    int n, i, m;
    char chars[MAX], code[MAX];
    int freq[MAX];
    struct Node* nodes[MAX];

    printf("Number of characters: ");
    scanf("%d", &n);
    printf("Chars: ");
    for (i = 0; i < n; i++)
        scanf(" %c", &chars[i]);
    printf("Freqs: ");
    for (i = 0; i < n; i++)
        scanf("%d", &freq[i]);

    for (i = 0; i < n; i++)
        nodes[i] = newNode(chars[i], freq[i]);
    m = n;                                   

    while (m > 1) {
        int i1 = 0, i2 = -1;
        for (i = 1; i < m; i++)
            if (nodes[i]->freq < nodes[i1]->freq) i1 = i;
        for (i = 0; i < m; i++) {
            if (i == i1) continue;
            if (i2 == -1 || nodes[i]->freq < nodes[i2]->freq) i2 = i;
        }

        struct Node* parent = newNode('$', nodes[i1]->freq + nodes[i2]->freq);
        parent->left  = nodes[i1];
        parent->right = nodes[i2];

        nodes[i1] = parent;        
        nodes[i2] = nodes[m - 1];    
        m--;
    }

    printf("\nCharacter  Code\n");
    printCodes(nodes[0], code, 0);
    return 0;
}
```

### Test
```
6
A B C D E F
5 9 12 13 16 45
-> A 1100, B 1101, C 100, D 101, E 111, F 0
```

### Complexity
- With a **min-heap / priority queue: O(n log n)** (n-1 merges, each O(log n)). Write this on paper.
- My simple array-scan version is O(n²), which is fine for the exam program and easier to type. Mention that a heap makes it O(n log n).
- Space: O(n)

### Viva
- *What is prefix-free?* No code is the beginning of another code, so decoding is unambiguous.
- *Why do frequent characters get shorter codes?* They are merged last, so they stay closer to the root.
- *Is the code unique?* The lengths are optimal, but exact bits can vary when frequencies tie.
- *Total bits for the example?* 5×4 + 9×4 + 12×3 + 13×3 + 16×3 + 45×1 = 224 bits.

---

# Q4. Topological Sort – Kahn's Algorithm (Exp 10b)

### Idea
Count the indegree of every vertex. Put all indegree-0 vertices in a queue. Remove one, add it to the answer, reduce the indegree of its neighbours, and enqueue any that reach 0. If you finish with fewer than V vertices processed, there is a **cycle**.

### Pseudocode
```
Kahn(V, adj):
    indegree[0..V-1] = 0
    for each edge u -> v:
        indegree[v]++
    queue = empty
    for v = 0 to V-1:
        if indegree[v] == 0: enqueue(v)
    count = 0
    while queue not empty:
        u = dequeue()
        add u to result; count++
        for each neighbour v of u:
            indegree[v]--
            if indegree[v] == 0: enqueue(v)
    if count != V:
        print "Cycle detected, topological sort impossible"
    else:
        print result
```

### C Code
```c
#include <stdio.h>
#define MAX 50

int adj[MAX][MAX];     
int deg[MAX];          
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
        adj[u][deg[u]++] = v;    
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
```

### Test
```
6 6
5 2
5 0
4 0
4 1
2 3
3 1
-> 4 5 2 0 3 1     (a different but VALID order from the sheet's 4 5 2 3 1 0; the sheet says multiple orders are accepted)

4 4
0 1
0 2
1 3
2 3
-> 0 1 2 3
```
Check the answer: for every edge u→v, u must appear before v.

### Complexity
- **O(V + E)** (every vertex enqueued once, every edge looked at once)
- Space: O(V + E) for the adjacency list, O(V) for queue and indegree

### Viva
- *Why does it only work on a DAG?* In a cycle no vertex ever reaches indegree 0, so it never gets processed.
- *How do you detect a cycle with it?* Processed count ≠ V.
- *Where is topological sort used?* Task scheduling, build order, course prerequisites.

---

# Q5. Cycle Detection in a Directed Graph – DFS (Exp 11c)

### Idea
Run DFS with two arrays:
- `visited[v]`: v has been reached before.
- `recStack[v]`: v is on the **current DFS path**.

If you meet a neighbour that is in `recStack`, that is a **back-edge, so there is a cycle**. When you finish a vertex, remove it from `recStack`.

### Pseudocode
```
DetectCycle(V, adj):
    visited[] = false, recStack[] = false
    for v = 0 to V-1:
        if not visited[v]:
            if DFS(v) == true:
                print "Cycle detected"; return
    print "No cycle found"

DFS(u):
    visited[u] = true
    recStack[u] = true
    for each neighbour v of u:
        if not visited[v]:
            if DFS(v) == true: return true
        else if recStack[v]:
            return true             // back-edge
    recStack[u] = false
    return false
```

### C Code
```c
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
            return 1;                
        }
    }
    recStack[u] = 0;                 
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
```

### Test
```
4 4
0 1
1 2
2 0
2 3
-> Cycle detected in the directed graph.

4 3
0 1
1 2
2 3
-> No cycle found in the directed graph.
```

### Complexity
- **O(V + E)**
- Space: O(V) for the arrays and recursion stack (plus the adjacency list)

### Viva
- *Why do we need recStack and not just visited?* An already-visited vertex is not always a cycle. In a DAG, two paths can reach the same vertex (a cross/forward edge). Only a vertex **on the current path** means a cycle.
- *Why run DFS from every vertex?* The graph may be disconnected.
- *Does the same code work for undirected graphs?* No, you would track the parent instead.

---

# Quick Revision Sheet

| Q | Algorithm | Type | Data structure | Time | Space |
|---|-----------|------|----------------|------|-------|
| 1 | Bucket Sort | Distribution sort | Array of buckets | Best/Avg O(n+k), Worst O(n²) | O(n+k) |
| 2 | Fractional Knapsack | Greedy | Sorted array by ratio | O(n log n) | O(n) |
| 3 | Huffman Coding | Greedy | Min-heap + binary tree | O(n log n) | O(n) |
| 4 | Kahn's Topo Sort | BFS | Queue + indegree array | O(V+E) | O(V+E) |
| 5 | DFS Cycle Detection | DFS | visited[] + recStack[] | O(V+E) | O(V) |

# Night-Before Checklist
- [ ] Type each program from memory once (start with Q4 and Q5, they are the shortest).
- [ ] Run each with both test cases.
- [ ] Practise writing pseudocode on paper without looking.
- [ ] Learn the one-line viva answers for each algorithm.
- [ ] In the exam: **pseudocode first** (it is 20 marks), then complexity, then code.