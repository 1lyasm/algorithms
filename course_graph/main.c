#include <stdio.h>
#include <stdlib.h>

struct Graph {
  int nodeCount;
  struct LList *nodes;
};

struct LListNode {
  int val;
  struct LListNode *next;
};

struct LList {
  struct LListNode *head;
};

int main() {
  // variables
  int n, **mat, i, j, parentCounts;
  struct Graph graph;

  // take n
  printf("n: ");
  scanf("%d", &n);

  // init matrix
  mat = malloc(n * sizeof(int *));
  for (i = 0; i < n; ++i) {
    mat[i] = malloc(n * sizeof(int));
  }

  // read to matrix
  for (i = 0; i < n; ++i) {
    for (j = 0; j < n; ++j) {
      scanf("%d", &mat[i][j]);
    }
  }

  // print matrix
  printf("\n\nInput: \n");
  for (i = 0; i < n; ++i) {
    for (j = 0; j < n; ++j) {
      printf("%d ", mat[i][j]);
    }
    printf("\n");
  }

  /*

    0 1 0 0 0
    0 0 0 1 0
    0 0 0 0 1
    0 0 0 0 1
    0 0 0 0 0

  */

  // compute node-parent count map
  parentCounts = malloc(n * sizeof(int));
  for (i = 0; i < n; ++i) {
    int parentCount = 0;
    for (j = 0; j < n; ++j) {
      if (mat[j][i] > 0) {
        ++parentCount;
      }
    }
  }
  free(parentCounts);
  parentCounts = 0;

  // init adj list
  graph.nodeCount = n;
  graph.nodes = malloc(n * sizeof(struct LList));
  for (i = 0; i < graph.nodeCount; ++i) {
    graph.nodes[i].head = 0;
    for (j = i; j < graph.nodeCount; ++j) {
      if (mat[i][j] > 0) {
        if (graph.nodes[i].head == 0) {
          graph.nodes[i].head = malloc(sizeof(struct LListNode));
          graph.nodes[i].head->next = 0;
        } else {
          // get to one before tail
          struct LListNode *tail = graph.nodes[i].head;
          struct LListNode *prevTail = tail;
          while (tail != 0) {
            prevTail = tail;
            tail = tail->next;
          }
          prevTail->next = malloc(sizeof(struct LListNode));
          prevTail->next->next = 0;
        }
      }
    }
  }

  // print adj list
  for (i = 0; i < graph.nodeCount; ++i) {
    struct LListNode *cur = graph.nodes[i].head;
    while (cur != 0) {
      printf("%d ", cur->val);
      cur = cur->next;
    }
    printf("\n");
  }

  // delete adj list
  for (i = 0; i < graph.nodeCount; ++i) {
    struct LListNode *cur = graph.nodes[i].head, *next;
    while (cur != 0) {
      next = cur->next;
      free(cur);
      cur = next;
    }
  }
  free(graph.nodes);
  graph.nodes = 0;

  // free matrix
  for (i = 0; i < n; ++i) {
    free(mat[i]);
    mat[i] = 0;
  }
  free(mat);
  mat = 0;

  return 0;
}
