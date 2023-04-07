#include <stdio.h>
#include "q2.h"
#include "../../include/arithmetic.h"
#include "../../include/character.h"

const int N_DIGITS = 8;

unsigned long hex_to_decimal(char hex_str[N_DIGITS + 1]){
    unsigned long res = 0;
    short int as_digit;
    char as_char = '\0';
    for (int i = N_DIGITS - 1; i >= 0; i--){
        as_char = hex_str[i];
        if (is_digit(as_char)){
                as_digit = as_char - 48;
            }
        else {
            as_digit = as_char - 55;
        }
        res += as_digit * comp_pow(16, (N_DIGITS - i - 1));
    }
    return res;
}
