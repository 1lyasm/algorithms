#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int val;
  int weight;
} Node;

void sssp(Node **, int *, int *, int, int, int *);
Node *getIncoming(Node **, int, int *, int *, int, int *);

void printGraph(Node **g, int *nodes, int *lens, int n) {
  int i;
  int j;
  for (i = 0; i < n; ++i) {
    printf("%d: ", nodes[i]);
    for (j = 0; j < lens[i]; ++j) {
      printf("%d-%d", g[i][j].val, g[i][j].weight);
      if (j != lens[i] - 1) {
        printf(",");
      }
    }
    printf("\n");
  }
}

void printIntArray(int *arr, int n, char *msg) {
  int i;
  printf("%s: ", msg);
  for (i = 0; i < n; ++i) {
    printf("%d", arr[i]);
    if (i != n - 1) {
      printf(", ");
    }
  }
  printf("\n");
}

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
  for (i = 0; i < n; ++i) {
      nodes[i] = i;
  }
  for (i = 2; i < fLen; ++i) {
    if (buf[i] == '\n') {
      ++j;
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
  printIntArray(nodes, n, "nodes");
  printGraph(g, nodes, lens, n);
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

void printIncoming(Node *incoming, int n, char *msg) {
  int i;
  printf("%s: ", msg);
  for (i = 0; i < n; ++i) {
    printf("{ val: %d, weight: %d }", incoming[i].val, incoming[i].weight);
    if (i != n - 1) {
      printf(", ");
    }
  }
  printf("\n");
}

void sssp(Node **g, int *nodes, int *memo, int n, int source, int *lens) {
  int i;
  int minVal;
  int j;
  printf("source: %d\n", source);
  memo[source] = 0;
  for (i = 0; i < n; ++i) {
    if (i != source) {
      int incomingLen;
      Node *incoming = getIncoming(g, n, nodes, lens, i, &incomingLen);
      printIncoming(incoming, incomingLen, "incoming");
      minVal = INT_MAX;
      for (j = 0; j < incomingLen; ++j) {
        int candidate = memo[incoming[j].val] + incoming[j].weight;
        if (candidate < minVal) {
          minVal = candidate;
        }
      }
      memo[i] = minVal;
      if (incomingLen > 0) {
        free(incoming);
      }
      printIntArray(memo, n, "memo");
    }
  }
}

Node *getIncoming(Node **g, int n, int *nodes, int *lens, int dest,
                  int *incomingLen) {
  int len = 0;
  int i;
  Node *incoming = NULL;
  int j;
  int k;
  printf("getIncoming: dest: %d\n", dest);
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
