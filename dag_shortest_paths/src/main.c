#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
    int val;
    int weight;
} Node;

void sssp(Node **, int *, int *, int, int, int *);
Node *getIncoming(Node **, int, int *, int *, int, int *);

int main() {
    FILE *fp = fopen("input.txt", "r");
    int fLen;
    int i;
    char *buf;
    fseek(fp, 0, SEEK_END);
    fLen = ftell(fp);
    buf = malloc((fLen + 1) * sizeof(char));
    fseek(fp, 0, SEEK_SET);
    fread(buf, sizeof(char), fLen, fp);
    Node **g;
    int *nodes;
    int n;
    int j = 0;
    int k = 0;
    int *lens;
    lens = malloc(16 * sizeof(int));
    for (i = 0; i < fLen; ++i) {
        if (buf[i] == '\n') {
            ++j;
            k = 0;
        }
        ++k;
        lens = realloc(lens, (j + 1) * sizeof(int));
        lens[j] = ceil((k - 3) / 4.0);
    }
    n = j;
    printf("n: %d\n", n);
    j = 0;
    g = malloc(n * sizeof(Node *));
    nodes = malloc(n * sizeof(int));
    nodes[0] = buf[0] - '0';
    for (i = 0; i < n; ++i) {
        printf("lens[%d]: %d\n", i, lens[i]);
        if (lens[i] > 0) {
            g[i] = malloc(lens[i] * sizeof(Node));
        } else {
            g[i] = NULL;
        }
    }
    k = 0;
    int m = 1;
    for (i = 2; i < fLen; ++i) {
        if (buf[i] == '\n') {
            ++j;
            if (i + 1 < fLen) {
                nodes[m] = buf[i + 1];
            }
            i += 2;
            k = 0;
        } else {
            printf("i: %d, k: %d, buf[i]: %c\n", i, k, buf[i]);
            g[j][k].val = buf[i] - '0';
            i += 2;
            g[j][k].weight = buf[i] - '0';
            if (i + 1 < fLen && buf[i + 1] != '\n') {
                i += 1;
            }
            ++k;
        }
    }
    int *memo;
    memo = malloc(n * sizeof(int));
    for (i = 0; i < n; ++i) {
        memo[i] = -1;
    }
    int source;
    printf("Enter source: ");
    scanf(" %d", &source);
    sssp(g, nodes, memo, n, source, lens);
    for (i = 0; i < n; ++i) {
        printf("Shortest path from node %d to %d: %d\n", source, i, memo[i]);
    }
    free(buf);
    free(lens);
    free(nodes);
    free(memo);
    for (i = 0; i < n; ++i) {
        free(g[i]);
    }
    free(g);
    return 0;
}

void sssp(Node **g, int *nodes, int *memo, int n, int source, int *lens) {
    int i;
    int minVal = (unsigned)(-1);
    int j;
    for (i = 0; i < n; ++i) {
        int incomingLen;
        Node *incoming = getIncoming(g, n, nodes, lens, i, &incomingLen);
        for (j = 0; j < incomingLen; ++j) {
            int candidate = incoming[j].val + incoming[j].weight;
            if (candidate < minVal) {
                minVal = candidate;
            }
        }
        memo[i] = minVal;
        if (incomingLen > 0) {
            free(incoming);
        }
    }
}

Node *getIncoming(Node **g, int n, int *nodes, int *lens, int dest, int *incomingLen) {
    int len = 0;
    int i;
    Node *incoming = NULL;
    int j;
    int k;
    k = 0;
    for (i = 0; i < n; ++i) {
        for (j = 0; j < lens[i]; ++j) {
            if (g[i][j].val == dest) {
                ++len;
            }
        }
    }
    if (len > 0) {
        incoming = malloc(len * sizeof(Node));
        for (i = 0; i < n; ++i) {
            for (j = 0; j < lens[i]; ++j) {
                if (g[i][j].val == dest) {
                    incoming[k].val = nodes[i];
                    incoming[k].weight = g[i][j].weight;
                    ++k;
                }
            }
        }
    }
    *incomingLen = len;
    return incoming;
}

