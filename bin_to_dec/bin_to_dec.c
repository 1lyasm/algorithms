#include <stdio.h>
#include "q1.h"
#include "../../include/arithmetic.h"

const int N_BITS = 16;

int binary_to_decimal(char bit_str[N_BITS + 1]){
    int res = 0;
    for (int i = N_BITS - 1; i >= 0; i--){
        res += (bit_str[i] - 48) * comp_pow(2, (N_BITS - i - 1));
    }
    return res;
}
