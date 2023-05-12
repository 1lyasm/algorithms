#include <stdio.h>
#include <stdlib.h>

struct GNode {
  int id;
  int isVisited;
};

int main() {
  int n;
  printf("n: ");
  scanf("%d", &n);

  int **mat = malloc(n * sizeof(int *));
  int *parentCounts = calloc(n, sizeof(int));
  int *childCounts = calloc(n, sizeof(int));
  struct GNode **adjList = malloc(n * sizeof(struct GNode *));

  printf("matrix:\n\n");
  for (int i = 0; i < n; ++i) {
    mat[i] = malloc(n * sizeof(int));
    for (int j = 0; j < n; ++j)
      scanf("%d", &mat[i][j]);
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      parentCounts[i] += (mat[j][i] > 0);
      childCounts[i] += (mat[i][j] > 0);
    }
    adjList[i] = malloc((childCounts[i] + 1) * sizeof(struct GNode));
    adjList[i][0].id = i + 1;
    adjList[i][0].isVisited = 0;
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0, top = 1; j < n; ++j) {
      if (mat[i][j] > 0) {
        adjList[i][top].id = j + 1;
        adjList[i][top++].isVisited = 0;
      }
    }
  }

  for (int termCounter = 1, courseLeft = 1; ; ++termCounter) {
    int hasPrintedTermNum = 0;
    courseLeft = 0;

    for (int i = 0; i < n; ++i) {
      if (parentCounts[i] == 0 && adjList[i][0].isVisited == 0) {
        if (hasPrintedTermNum == 0) {
          printf("\nterm %d: ", termCounter);
          hasPrintedTermNum = 1;
        }
        printf("course %d ", i + 1);
        adjList[i][0].isVisited = 1;
        courseLeft = 1;
        for (int j = 1; j < childCounts[i] + 1; ++j)
          parentCounts[adjList[i][j].id - 1] -= n;
      }
    }

    for (int i = 0; i < n; ++i) {
      if (parentCounts[i] < 0)
        parentCounts[i] += n - 1;
    }

    if (courseLeft == 0) {
      break;
    }
  }

  for (int i = 0; i < n; ++i) {
    if (adjList[i][0].isVisited == 0) {
      printf("\nAdditional courses left, unable to graduate\n");
      break;
    }
  }

  for (int i = 0; i < n; ++i) {
    free(adjList[i]);
    free(mat[i]);
  }
  free(adjList);
  free(childCounts);
  free(parentCounts);
  free(mat);

  return 0;
}
