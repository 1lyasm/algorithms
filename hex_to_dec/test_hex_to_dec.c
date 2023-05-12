#include <assert.h>
#include <stdio.h>

#include "q2.h"

void test_hex_to_decimal();

int main() {
  test_hex_to_decimal();
  return 0;
}

void test_hex_to_decimal() {
  printf("%s", "test_hex_to_decimal ... ");
  assert(hex_to_decimal("FFFFFFFF") == 4294967295);
  assert(hex_to_decimal("AAAAAAAA") == 2863311530);
  assert(hex_to_decimal("123AAA34") == 305834548);
  assert(hex_to_decimal("00000001") == 1);
  assert(hex_to_decimal("00000011") == 17);
  assert(hex_to_decimal("ABCDEF12") == 2882400018);
  assert(hex_to_decimal("12ABCDEF") == 313249263);
  assert(hex_to_decimal("01200210") == 18874896);
  assert(hex_to_decimal("10000000") == 268435456);
  assert(hex_to_decimal("A1B2C3D4") == 2712847316);
  assert(hex_to_decimal("FFFFFFF0") == 4294967280);
  assert(hex_to_decimal("0FFFFFF0") == 268435440);
  printf("%s", "OK\n");
  return;
}
