#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

static void merge(int *array, unsigned start, unsigned midpoint, unsigned end,
                  unsigned *n_inverse) {
  printf("merge called, n_inverse: %u\n", *n_inverse);
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

      ++(*n_inverse);
    }
    ++array_index;
  }
  unsigned rem_is_left = 0;
  if (left <= buffer_midpoint) {
    remaining = left;
    limit = buffer_midpoint;
    rem_is_left = 1;
  } else {
    remaining = right;
    limit = buffer_end;
  }
  if (rem_is_left) {
    printf("rem_is_left: ");
    for (unsigned i = start; i <= end; ++i) {
      printf("%d ", buffer[i - start]);
    }
    printf("\n");
    printf("n_inverse: %u\n", *n_inverse);
  }
  while (remaining <= limit) {
    array[array_index] = buffer[remaining];
    ++array_index;
    ++remaining;
    if (rem_is_left) {
      ++(*n_inverse);
    }
  }
  printf("exiting merge, n_inverse: %u\n\n", *n_inverse);
  free(buffer);
}

static void merge_sort(int *array, unsigned start, unsigned end,
                       unsigned *n_inverse) {
  unsigned array_len = end + 1 - start;
  /* printf("%s: start: %u, end: %u\n", __func__, start, end); */
  if (array_len > 1) {
    unsigned midpoint = (start + end) / 2;
    merge_sort(array, start, midpoint, n_inverse);
    merge_sort(array, midpoint + 1, end, n_inverse);

    /* printf("%s: before merging:\n\t", __func__); */
    /* print_array(array, start, end); */

    merge(array, start, midpoint, end, n_inverse);

    /* printf("%s: after merging:\n\t", __func__); */
    /* print_array(array, start, end); */
  }
}

unsigned cnt_inverse(int *nums, unsigned n) {
  unsigned n_inverse = 0;
  merge_sort(nums, 0, n - 1, &n_inverse);
  return n_inverse;
}

int main() {
  {
    int nums[] = {2, 4, 3, 6, 7, 5, 9, 8};
    unsigned n = sizeof(nums) / sizeof(nums[0]);
    unsigned n_inverse = cnt_inverse(nums, n);
    printf("n_inverse: %u\n", n_inverse);
    assert(n_inverse == 4);
  }
  /* { */
  /*     int nums[] = {1, 5, 7, 2, 8, 6}; */
  /*     unsigned n = sizeof(nums) / sizeof(nums[0]); */
  /*     unsigned n_inverse = cnt_inverse(nums, n); */
  /*     printf("n_inverse: %u\n", n_inverse); */
  /*     assert(n_inverse == 4); */
  /*   } */

  return 0;
}
