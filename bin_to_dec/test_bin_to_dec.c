#include <assert.h>
#include <stdio.h>

#include "q1.h"

void test_binary_to_decimal();

int main() {
  test_binary_to_decimal();
  return 0;
}

void test_binary_to_decimal() {
  printf("%s", "test_binary_to_decimal ...");
  assert(binary_to_decimal("1000100010001000") == 34952);
  assert(binary_to_decimal("1101111001000011") == 56899);
  assert(binary_to_decimal("0010000110111100") == 8636);
  assert(binary_to_decimal("1111000011110000") == 61680);
  assert(binary_to_decimal("0000000000000011") == 3);
  assert(binary_to_decimal("1000000000000000") == 32768);
  assert(binary_to_decimal("1010101010101010") == 43690);
  assert(binary_to_decimal("0101010101010110") == 21846);
  assert(binary_to_decimal("0101101110110100") == 23476);
  printf("%s", " OK\n");
  return;
}
