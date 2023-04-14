#include "../../include/character.h"
#include "q3_4.h"
#include <stdio.h>
#include <string.h>

void convert_from_decimal(unsigned long decimal, int base, char *bit_str,
                          int bit_str_len) {
  unsigned long whole_part = decimal;
  int remainder;
  int i;
  for (i = bit_str_len - 1; whole_part > 0; i--) {
    remainder = whole_part % base;
    if (remainder > 9) {
      bit_str[i] = (char)(remainder + 55);
    } else {
      bit_str[i] = (char)(remainder + 48);
    }
    whole_part /= base;
  }
  for (int j = i; j >= 0; j--) {
    bit_str[j] = '0';
  }
  return;
}
