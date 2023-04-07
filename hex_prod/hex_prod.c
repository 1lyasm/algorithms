#include <stdlib.h>
#include <string.h>
#include "q7.h"
#include "q2.h"
#include "q5_6.h"
#include "../../include/character.h"

char* hex_product(char short_hex, char* long_hex){
    const int HEX_BASE = 16;
    int len_long_hex = strlen(long_hex);
    if (short_hex == '0'){
        char* zero_str = malloc(2);
        zero_str[0] = '0';
        zero_str[1] = '\0';
        return zero_str;
    }
    if (short_hex == '1'){
        char* product_str = malloc(len_long_hex + 1);
        return strcpy(product_str, long_hex);
    }
    int len_product = len_long_hex + 1;
    char* product_str = malloc(len_product + 1);
    product_str[len_product] = '\0';
    for (int i = 0; i < len_product; i++){
        product_str[i] = '0';
    }
    int short_decimal = to_digit(short_hex);
    for (int i = 0; i < short_decimal; i++){
        product_str = add_in_base(product_str, long_hex, HEX_BASE);
        len_product += 1;
    }
    int last_zero_idx = 0;
    for (; (last_zero_idx < len_product) && (product_str[last_zero_idx] == '0');
        last_zero_idx++);
    char* trimmed_product_str = malloc(len_product + 1 - last_zero_idx);
    trimmed_product_str[len_product - last_zero_idx] = '\0';
    for (int i = len_product - 1, j = len_product - last_zero_idx - 1;
        (i >= 0) && (i >= last_zero_idx); i--, j--){
        trimmed_product_str[j] = product_str[i];
    }
    free(product_str);
    return trimmed_product_str;
}
