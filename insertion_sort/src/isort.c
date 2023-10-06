#include <stdio.h>
#include <stdlib.h>

static void print_array(int *array, unsigned array_len) {
  printf("%s: array of len %d:\n\t", __func__, array_len);
  for (unsigned i = 0; i < array_len; ++i) {
    printf("%d", array[i]);
    if (i != array_len - 1) {
      printf(", ");
    }
  }
  printf("\n");
}

static void insertion_sort(int *array, unsigned array_len) {
    printf("%s: called with array_len: %d\n", __func__, array_len);
    for (int i = 1; (unsigned)i < array_len; ++i) {
        int key = array[i];
        int j = i - 1;
        while (j >= 0 && key < array[j]) {
            array[j + 1] = array[j];
            --j;
        }
        array[j + 1] = key;
    }
}

int main() {
  {
    int array[] = {5, 3, 4, 2, 1};
    unsigned array_len = sizeof(array) / sizeof(array[0]);
    insertion_sort(array, array_len);
    print_array(array, array_len);
  }
  {
    int array[] = {5, 4, 3, 2, 1};
    unsigned array_len = sizeof(array) / sizeof(array[0]);
    insertion_sort(array, array_len);
    print_array(array, array_len);
  }
  {
    int array[] = {1, 2, 3, 4, 5};
    unsigned array_len = sizeof(array) / sizeof(array[0]);
    insertion_sort(array, array_len);
    print_array(array, array_len);
  }
  {
    int array[] = {6, 5, 3, 1, 8, 7, 2, 4};
    unsigned array_len = sizeof(array) / sizeof(array[0]);
    insertion_sort(array, array_len);
    print_array(array, array_len);
  }
}
