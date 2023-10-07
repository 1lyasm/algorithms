#include <stdio.h>
#include <stdlib.h>

static void print_array(int *array, unsigned start, unsigned end) {
  printf("%s: array of len: %d\n\t", __func__, end + 1 - start);
  for (unsigned i = start; i <= end; ++i) {
    printf("%d", array[i]);
    if (i != end) {
      printf(", ");
    }
  }
  printf("\n");
}

static void merge(int *array, unsigned start, unsigned midpoint, unsigned end) {
  int *buffer = malloc((end - start + 1) * sizeof(int));
  unsigned buffer_start = 0, buffer_midpoint = midpoint - start,
           buffer_end = end - start;
  unsigned left = buffer_start, right = buffer_midpoint + 1;
  unsigned array_index = start;
  unsigned remaining;
  unsigned limit;
  /* printf("%s: start: %u, midpoint: %u, end: %u, buffer_start: %u, " */
         /* "buffer_midpoint: %u, buffer_end: %u\n", */
         /* __func__, start, midpoint, end, buffer_start, buffer_midpoint, */
         /* buffer_end); */
  for (unsigned i = start; i <= end; ++i) {
    buffer[i - start] = array[i];
  }
  while (left <= buffer_midpoint && right <= buffer_end) {
    if (buffer[left] < buffer[right]) {
      array[array_index] = buffer[left];
      ++left;
    } else {
      array[array_index] = buffer[right];
      ++right;
    }
    ++array_index;
  }
  if (left <= buffer_midpoint) {
    remaining = left;
    limit = buffer_midpoint;
  } else {
    remaining = right;
    limit = buffer_end;
  }
  while (remaining <= limit) {
    array[array_index] = buffer[remaining];
    ++array_index;
    ++remaining;
  }
  free(buffer);
}

static void merge_sort(int *array, unsigned start, unsigned end) {
  unsigned array_len = end + 1 - start;
  /* printf("%s: start: %u, end: %u\n", __func__, start, end); */
  if (array_len > 1) {
    unsigned midpoint = (start + end) / 2;
    merge_sort(array, start, midpoint);
    merge_sort(array, midpoint + 1, end);

    /* printf("%s: before merging:\n\t", __func__); */
    /* print_array(array, start, end); */

    merge(array, start, midpoint, end);

    /* printf("%s: after merging:\n\t", __func__); */
    /* print_array(array, start, end); */
  }
}

int main() {
  {
    int array[] = {6, 5, 3, 1, 8, 7, 2, 4};
    unsigned array_len = sizeof(array) / sizeof(array[0]);
    merge_sort(array, 0, array_len - 1);
    print_array(array, 0, array_len - 1);
  }
  {
    int array[] = {1, 2, 3, 4, 5};
    unsigned array_len = sizeof(array) / sizeof(array[0]);
    merge_sort(array, 0, array_len - 1);
    print_array(array, 0, array_len - 1);
  }
  {
    int array[] = {5, 4, 3, 2, 1};
    unsigned array_len = sizeof(array) / sizeof(array[0]);
    merge_sort(array, 0, array_len - 1);
    print_array(array, 0, array_len - 1);
  }
  {
    int array[] = {2, 1, 3, 1, 4, 1, 3};
    unsigned array_len = sizeof(array) / sizeof(array[0]);
    merge_sort(array, 0, array_len - 1);
    print_array(array, 0, array_len - 1);
  }
}

