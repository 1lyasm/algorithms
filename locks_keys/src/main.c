#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

void match(int *locks, int *keys, int low, int high) {
  if (low < high) {
    int key_index = low + rand() % (high - low);
    int pivot = partition(locks, low, high, keys[key_index]);

    partition(keys, low, high, locks[pivot]);

    match(locks, keys, low, pivot - 1);
    match(locks, keys, pivot + 1, high);
  }
}

void assert_arr_eq(int *arr1, int *arr2, int len) {
  int i;
  for (i = 0; i < len; ++i) {
    assert(arr1[i] == arr2[i]);
  }
}

int main() {
  srand((unsigned)time(0));
  {
    int locks[] = {2, 1, 4, 5, 3};
    int keys[] = {5, 2, 4, 3, 1};
    int n = sizeof(locks) / sizeof(locks[0]);
    int sorted[] = {1, 2, 3, 4, 5};
    printArr("keys before match", keys, n);
    printArr("locks before match", locks, n);
    match(locks, keys, 0, n - 1);
    printArr("keys after match", keys, n);
    printArr("locks after match", locks, n);
    assert_arr_eq(locks, sorted, n);
    assert_arr_eq(keys, sorted, n);
    printf("\n");
  }
  {
    int locks[] = {4, 3, 5, 1, 2};
    int keys[] = {2, 5, 4, 3, 1};
    int n = sizeof(locks) / sizeof(locks[0]);
    int sorted[] = {1, 2, 3, 4, 5};
    printArr("keys before match", keys, n);
    printArr("locks before match", locks, n);
    match(locks, keys, 0, n - 1);
    printArr("keys after match", keys, n);
    printArr("locks after match", locks, n);
    assert_arr_eq(locks, sorted, n);
    assert_arr_eq(keys, sorted, n);
    printf("\n");
  }
  return 0;
}
