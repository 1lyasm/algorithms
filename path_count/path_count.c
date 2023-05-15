#include <stdio.h>
#include <stdlib.h>

void take_n(int *n) {
  printf("n: ");
  scanf("%d", n);
}

void read_matrix(int mat[256][256], int n) {
  int i, j;
  printf("Enter matrix: \n");
  for (i = 0; i < n; ++i) {
    for (j = 0; j < n; ++j) {
      scanf("%d", &mat[i][j]);
    }
  }
}

void print_matrix(int mat[256][256], int n) {
  int i, j;
  printf("Matrix: \n");
  for (i = 0; i < n; ++i) {
    for (j = 0; j < n; ++j) {
      printf("%d ", mat[i][j]);
    }
    printf("\n");
  }
}

void find_path(int mat[256][256],
  int x, int y, int n, int *path_count, int path[256][2], int *path_top) {
  int i;
  if (x == n - 1 && y == n - 1) {
    path[*path_top][0] = x;
    path[*path_top][1] = y;
    ++*path_count;
    ++*path_top;
    for (i = 0; i < *path_top; ++i) {
      printf("(%d, %d) ", path[i][0], path[i][1]);
    }
    printf("\n");
    return;
  }
  if (x >= n || y >= n) {
    return;
  }
  if (mat[x][y] == 0) {
    return;
  }
  else {
    path[*path_top][0] = x;
    path[*path_top][1] = y;
    ++*path_top; 
  }
  int path_copy[256][2];
  for (i = 0; i < *path_top; ++i) {
    path_copy[i][0] = path[i][0];
    path_copy[i][1] = path[i][1];
  }
  int path_top_copy = *path_top;
  find_path(mat, x + 1, y, n, path_count, path, path_top);
  find_path(mat, x, y + 1, n, path_count, path_copy, &path_top_copy);
}

int main() {
  int n;
  int mat[256][256];
  int i, j;
  int path_count = 0;
  int path[256][2];
  int path_top = 0;

  take_n(&n);
  read_matrix(mat, n);
  print_matrix(mat, n);
  find_path(mat, 0, 0, n, &path_count, path, &path_top);
  printf("\nTotal path count: %d\n", path_count);

  printf("\n");
  return 0;
}
