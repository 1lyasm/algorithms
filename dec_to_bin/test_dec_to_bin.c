#include "q3_4.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

void test_convert_from_decimal_to_binary();
void test_convert_from_decimal_to_hex();

int main() {
  test_convert_from_decimal_to_binary();
  test_convert_from_decimal_to_hex();
  return 0;
}

void test_convert_from_decimal_to_binary() {
  printf("%s", "test_convert_from_decimal_to_binary ... ");
  const int BIT_CNT = 32;
  char bit_str[BIT_CNT + 1];
  bit_str[BIT_CNT] = '\0';
  const int BASE = 2;
  const int DIGIT_CNT = BIT_CNT / 4;
  convert_from_decimal(16, BASE, bit_str, BIT_CNT);
  assert(strcmp(bit_str, "00000000000000000000000000010000") == 0);
  convert_from_decimal(61, BASE, bit_str, BIT_CNT);
  assert(strcmp(bit_str, "00000000000000000000000000111101") == 0);
  convert_from_decimal(0, BASE, bit_str, BIT_CNT);
  assert(strcmp(bit_str, "00000000000000000000000000000000") == 0);
  convert_from_decimal(128, BASE, bit_str, BIT_CNT);
  assert(strcmp(bit_str, "00000000000000000000000010000000") == 0);
  convert_from_decimal(51416416, BASE, bit_str, BIT_CNT);
  assert(strcmp(bit_str, "00000011000100001000110101100000") == 0);
  convert_from_decimal(113135424, BASE, bit_str, BIT_CNT);
  assert(strcmp(bit_str, "00000110101111100100111101000000") == 0);
  convert_from_decimal(215005100, BASE, bit_str, BIT_CNT);
  assert(strcmp(bit_str, "00001100110100001011011110101100") == 0);
  convert_from_decimal(3, BASE, bit_str, BIT_CNT);
  assert(strcmp(bit_str, "00000000000000000000000000000011") == 0);
  convert_from_decimal(1111111, BASE, bit_str, BIT_CNT);
  assert(strcmp(bit_str, "00000000000100001111010001000111") == 0);
  convert_from_decimal(2222, BASE, bit_str, BIT_CNT);
  assert(strcmp(bit_str, "00000000000000000000100010101110") == 0);
  convert_from_decimal(503, BASE, bit_str, BIT_CNT);
  assert(strcmp(bit_str, "00000000000000000000000111110111") == 0);
  convert_from_decimal(63, BASE, bit_str, BIT_CNT);
  assert(strcmp(bit_str, "00000000000000000000000000111111") == 0);
  convert_from_decimal(65, BASE, bit_str, BIT_CNT);
  assert(strcmp(bit_str, "00000000000000000000000001000001") == 0);
  convert_from_decimal(4294966062, BASE, bit_str, BIT_CNT);
  assert(strcmp(bit_str, "11111111111111111111101100101110") == 0);
  convert_from_decimal(4294967295, BASE, bit_str, BIT_CNT);
  assert(strcmp(bit_str, "11111111111111111111111111111111") == 0);
  convert_from_decimal(0, BASE, bit_str, BIT_CNT);
  assert(strcmp(bit_str, "00000000000000000000000000000000") == 0);
  printf("%s", "OK\n");
  return;
}

void test_convert_from_decimal_to_hex() {
  printf("%s", "test_convert_from_decimal_to_hex ... ");
  const int DIGIT_CNT = 8;
  char bit_str[DIGIT_CNT + 1];
  bit_str[DIGIT_CNT] = '\0';
  const int BASE = 16;
  convert_from_decimal(61, BASE, bit_str, DIGIT_CNT);
  assert(strcmp(bit_str, "0000003D") == 0);
  convert_from_decimal(0, BASE, bit_str, DIGIT_CNT);
  assert(strcmp(bit_str, "00000000") == 0);
  convert_from_decimal(128, BASE, bit_str, DIGIT_CNT);
  assert(strcmp(bit_str, "00000080") == 0);
  convert_from_decimal(51416416, BASE, bit_str, DIGIT_CNT);
  assert(strcmp(bit_str, "03108D60") == 0);
  convert_from_decimal(113135424, BASE, bit_str, DIGIT_CNT);
  assert(strcmp(bit_str, "06BE4F40") == 0);
  convert_from_decimal(215005100, BASE, bit_str, DIGIT_CNT);
  assert(strcmp(bit_str, "0CD0B7AC") == 0);
  convert_from_decimal(3, BASE, bit_str, DIGIT_CNT);
  assert(strcmp(bit_str, "00000003") == 0);
  convert_from_decimal(1111111, BASE, bit_str, DIGIT_CNT);
  assert(strcmp(bit_str, "0010F447") == 0);
  convert_from_decimal(2222, BASE, bit_str, DIGIT_CNT);
  assert(strcmp(bit_str, "000008AE") == 0);
  convert_from_decimal(503, BASE, bit_str, DIGIT_CNT);
  assert(strcmp(bit_str, "000001F7") == 0);
  convert_from_decimal(63, BASE, bit_str, DIGIT_CNT);
  assert(strcmp(bit_str, "0000003F") == 0);
  convert_from_decimal(65, BASE, bit_str, DIGIT_CNT);
  assert(strcmp(bit_str, "00000041") == 0);
  convert_from_decimal(4294966062, BASE, bit_str, DIGIT_CNT);
  assert(strcmp(bit_str, "FFFFFB2E") == 0);
  convert_from_decimal(4294967295, BASE, bit_str, DIGIT_CNT);
  assert(strcmp(bit_str, "FFFFFFFF") == 0);
  convert_from_decimal(0, BASE, bit_str, DIGIT_CNT);
  assert(strcmp(bit_str, "00000000") == 0);
  printf("%s", "OK\n");
  return;
}
