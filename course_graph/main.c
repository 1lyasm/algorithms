#include <stdio.h>
#include <stdlib.h>

struct GNode {
  int id;
  int isVisited;
};

int main() {
  // variables
  int n;
  int **mat = 0;
  int i;
  int j;
  int termCounter = 1;
  int courseLeft = 1;
  int isCyclic = 0;
  struct GNode **adjList;
  int *parentCounts;
  int *childCounts;

  // take n
  printf("n: ");
  scanf("%d", &n);

  // init matrix
  printf("matrix: \n\n");
  mat = malloc(n * sizeof(int *));
  for (i = 0; i < n; ++i) {
    mat[i] = malloc(n * sizeof(int));
    for (j = 0; j < n; ++j) {
      scanf("%d", &mat[i][j]);
    }
  }
  printf("\n");

  // init graph
  childCounts = calloc(n, sizeof(int));
  parentCounts = calloc(n, sizeof(int));
  adjList = malloc(n * sizeof(struct GNode *));
  for (i = 0; i < n; ++i) {
    // fill parenCounts and childCounts
    for (j = 0; j < n; ++j) {
      if (mat[j][i] > 0) {
        ++parentCounts[i];
      }
      if (mat[i][j] > 0) {
        ++childCounts[i];
      }
    }

    // allocate just enough space for a list
    adjList[i] = malloc((childCounts[i] + 1) * sizeof(struct GNode));

    // put node itself as first element of each list
    adjList[i][0].id = i + 1;
    adjList[i][0].isVisited = 0;
  }

  for (i = 0; i < n; ++i) {
    int top = 1;
    for (j = 0; j < n; ++j) {
      if (mat[i][j] > 0) {
        adjList[i][top].id = j + 1;
        adjList[i][top].isVisited = 0;
        top++;
      }
    }
  }

  // print terms and courses
  while (courseLeft == 1) {
    int hasPrintedTermNum = 0;
    courseLeft = 0;
    for (i = 0; i < n; ++i) {
      if (parentCounts[i] == 0 && adjList[i][0].isVisited == 0) {
        if (hasPrintedTermNum == 0) {
          printf("term %d: ", termCounter);
          hasPrintedTermNum = 1;
        }
        printf("course %d ", i + 1);
        adjList[i][0].isVisited = 1;
        courseLeft = 1;
        for (j = 1; j < childCounts[i] + 1; ++j) {
          parentCounts[adjList[i][j].id - 1] -= n;
        }
      }
    }
    for (i = 0; i < n; ++i) {
      if (parentCounts[i] < 0) {
        parentCounts[i] += n - 1;
      }
    }
    printf("\n");
    ++termCounter;
  }

  // check that every node is visited
  for (i = 0; i < n && isCyclic == 0; ++i) {
    if (adjList[i][0].isVisited == 0) {
      printf("Additional courses left, unable to graduate\n");
      isCyclic = 1;
    }
  }

  // free everything
  for (i = 0; i < n; ++i) {
    free(adjList[i]);
    free(mat[i]);
  }
  free(adjList);
  free(childCounts);
  free(parentCounts);
  free(mat);

  return 0;
}
