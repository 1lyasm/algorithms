#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/character.h"
#include "q5_6.h"

char *add_in_base(char *t1, char *t2, int base) {
  int len_t1 = strlen(t1), len_t2 = strlen(t2);
  char **smaller_str_ptr = (len_t1 >= len_t2) ? (&t2) : &(t1);
  char **bigger_str_ptr = (len_t1 < len_t2) ? (&t2) : &(t1);
  int smaller_len = strlen(*smaller_str_ptr),
      bigger_len = strlen(*bigger_str_ptr);
  char *sum_str = malloc(bigger_len + 2);
  sum_str[bigger_len + 1] = '\0';
  char *padded_str = malloc(bigger_len + 1);
  padded_str[bigger_len] = '\0';
  for (int i = 0; i <= smaller_len - 1; i++) {
    padded_str[bigger_len - 1 - i] = (*(smaller_str_ptr))[smaller_len - 1 - i];
  }
  for (int i = smaller_len + 1; i <= bigger_len; i++) {
    padded_str[bigger_len - i] = '0';
  }
  int vertical_sum, carry = 0, remainder;
  for (int i = bigger_len - 1; i >= 0; i--) {
    vertical_sum =
        to_digit(padded_str[i]) + to_digit((*(bigger_str_ptr))[i]) + carry;
    carry = (int)(vertical_sum >= base);
    remainder = vertical_sum - carry * base;
    sum_str[i + 1] = from_digit(remainder);
  }
  sum_str[0] = from_digit(carry);
  return sum_str;
}
