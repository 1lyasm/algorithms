#include <stdio.h>

void printArr(char *msg, int *arr, int len) {
  int i;
  printf("%s: ", msg);
  for (i = 0; i < len; ++i) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

int partition(int *arr, int low, int high, int pivot) {
  int i = low;
  int j;
  int temp1, temp2;

  for (j = low; j < high; j++) {
    if (arr[j] < pivot) {
      temp1 = arr[i];
      arr[i] = arr[j];
      arr[j] = temp1;
      i++;
    } else if (arr[j] == pivot) {
      temp1 = arr[j];
      arr[j] = arr[high];
      arr[high] = temp1;
      j--;
    }
  }
  temp2 = arr[i];
  arr[i] = arr[high];
  arr[high] = temp2;

  return i;
}

void matchPairs(int *locks, int *keys, int low, int high) {
  if (low < high) {
    int pivot = partition(locks, low, high, keys[high]);

    partition(keys, low, high, locks[pivot]);

    matchPairs(locks, keys, low, pivot - 1);
    matchPairs(locks, keys, pivot + 1, high);
  }
}

int main() {
  int locks[] = {2, 1, 4, 5, 3};
  int keys[] = {5, 2, 4, 3, 1};
  int n = sizeof(locks) / sizeof(locks[0]);
  matchPairs(locks, keys, 0, n - 1);
  printArr("locks", locks, n);
  printArr("keys", locks, n);
  return 0;
}

