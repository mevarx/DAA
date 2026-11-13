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
    if (root->left == NULL && root->right == NULL) {   /* leaf */
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
    m = n;                                   /* nodes currently in the list */

    while (m > 1) {
        int i1 = 0, i2 = -1;
        /* smallest */
        for (i = 1; i < m; i++)
            if (nodes[i]->freq < nodes[i1]->freq) i1 = i;
        /* second smallest */
        for (i = 0; i < m; i++) {
            if (i == i1) continue;
            if (i2 == -1 || nodes[i]->freq < nodes[i2]->freq) i2 = i;
        }

        struct Node* parent = newNode('$', nodes[i1]->freq + nodes[i2]->freq);
        parent->left  = nodes[i1];
        parent->right = nodes[i2];

        nodes[i1] = parent;          /* parent takes the first slot   */
        nodes[i2] = nodes[m - 1];    /* last node fills the second    */
        m--;
    }

    printf("\nCharacter  Code\n");
    printCodes(nodes[0], code, 0);
    return 0;
}