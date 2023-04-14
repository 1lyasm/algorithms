#include <cassert>
#include <cmath>
#include <cstdlib>
#include <iostream>

void fill_char_arr(char dest_arr[], int size);
int convert_to_decimal(const char source_arr[], int size);
void test_convert_to_decimal();
int get_operand(char at_hand);

int main() {
  const char HEX_DIGITS[15] = {'1', '2', '3', '4', '5', '6', '7', '8',
                               '9', 'a', 'b', 'c', 'd', 'e', 'f'};
  const int MAX_SIZE = 10;
  char hex_num[MAX_SIZE]{};
  fill_char_arr(hex_num, MAX_SIZE);
  int decimal = convert_to_decimal(hex_num, MAX_SIZE);
  test_convert_to_decimal();
  if (decimal > 0)
    std::cout << decimal;
  else {
    std::cout << "Addition overflow";
  }

  std::cout << '\n';
  return 0;
}

void fill_char_arr(char dest_arr[], int size) {
  std::cout << "In hex: ";
  char input_char;
  std::cin.get(input_char);
  for (int i = 0; i < size && input_char != '\n'; i++) {
    dest_arr[i] = input_char;
    std::cin.get(input_char);
  }
  return;
}

int convert_to_decimal(const char source_arr[], int size) {
  int decimal_sum(0), i, operand(0);
  char char_at_hand;
  for (i = size - 1; i >= 0 && !(source_arr[i]); i--)
    ;
  for (int j = i; j >= 0 && decimal_sum <= 10000000000; j--) {
    char_at_hand = source_arr[j];
    if (isdigit(char_at_hand))
      operand = char_at_hand - 48;
    else
      operand = get_operand(char_at_hand);
    decimal_sum += operand * static_cast<int>(std::pow(16, i - j));
  }
  if (decimal_sum > 10000000000 || decimal_sum < 0)
    return -1;
  else
    return decimal_sum;
}

void test_convert_to_decimal() {
  char hex1[6] = {'a', 'b', 'c', '7', '5', '3'};
  char hex2[6] = {'c', 'd', 'f', '7', '5', '0'};
  char hex3[6] = {'9', '5', '7', '3', '8', '2'};
  char hex4[6] = {'a', 'a', 'a', 'a', 'a', 'a'};
  char hex5[3] = {'a', 'b', 'c'};
  char hex6[8] = {'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e'};
  assert(convert_to_decimal(hex1, 6) == 11257683);
  assert(convert_to_decimal(hex2, 6) == 13498192);
  assert(convert_to_decimal(hex3, 6) == 9794434);
  assert(convert_to_decimal(hex4, 6) == 11184810);
  assert(convert_to_decimal(hex5, 3) == 2748);
  assert(convert_to_decimal(hex6, 8) == -1);
  return;
}

int get_operand(char at_hand) {
  const char HEX_LETTERS[6] = {'a', 'b', 'c', 'd', 'e', 'f'};
  for (int i = 10; i < 16; i++) {
    if (HEX_LETTERS[i - 10] == at_hand)
      return i;
  }
  return 0;
}