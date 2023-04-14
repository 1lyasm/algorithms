#include <stdio.h>

int count_long_subarray(int *A, int size) {
  int subl = 1;
  int maxl = subl;
  // int count = 1;
  for (int i = 1; i < size; i++) {
    if (A[i] > A[i - 1]) {
      subl++;
    } else {
      subl = 1;
    }
    if (subl > maxl) {
      maxl = subl;
      count = 1;
    } else if (subl == maxl) {
      count++;
    }
  }
  return count;
}

int main() {
  int A[5] = {2, 2, 4, 1, 4};
  printf("%d\n", count_long_subarray(A, 5));

  int B[8] = {7, 8, 5, 7, 7, 3, 2, 8};
  printf("%d\n", count_long_subarray(B, 8));

  int C[11] = {7, 7, 9, 1, 2, 11, 9, 6, 2, 8, 9};
  printf("%d\n", count_long_subarray(C, 11));

  int D[18] = {4, 18, 10, 8, 13, 16, 18, 1, 9, 6, 11, 13, 12, 5, 7, 17, 13, 3};
  printf("%d\n", count_long_subarray(D, 18));

  int E[25] = {11, 16, 10, 19, 20, 18, 3, 19, 2,  1,  8, 17, 7,
               13, 1,  11, 1,  18, 19, 9, 7,  19, 24, 2, 12};
  printf("%d\n", count_long_subarray(E, 25));

  return 0;
}
