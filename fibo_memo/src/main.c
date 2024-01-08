/* Program that prints n-th fibonacci number */
/* using recursion and memoization */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int fib(int n, int *memo) {
  if (memo[n] != -1) {
    return memo[n];
  }
  memo[n] = fib(n - 1, memo) + fib(n - 2, memo);
  return memo[n];
}

int main() {
  int *memo;
  int i;
  int n;
  printf("Enter n: ");
  scanf("%d", &n);
  memo = malloc(n * sizeof(int));
  for (i = 0; i < n; ++i) {
    memo[i] = -1;
  }
  memo[0] = 0;
  memo[1] = 1;
  for (i = 0; i < n; ++i) {
    printf("%d", fib(i, memo));
    if (i != n - 1) {
        printf(", ");
    }
  }
  printf("\n");
  free(memo);
  return 0;
}
