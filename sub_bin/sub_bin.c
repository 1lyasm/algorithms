#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "q5_6.h"
#include "q9.h"
#include "../../include/character.h"

char* one_complement(char* binary_str, int len_compl){
    int bin_len = strlen(binary_str);
    assert(len_compl >= bin_len);
    char* compl_str = malloc(len_compl + 1);
    compl_str[len_compl] = '\0';
    int compl_idx = len_compl - 1, bin_idx = bin_len - 1;
    for (; bin_idx >= 0; compl_idx--, bin_idx--){
        compl_str[compl_idx] = from_digit(abs(binary_str[bin_idx] - 49));
    }
    for (; compl_idx >= 0; compl_idx--){
        compl_str[compl_idx] = '1';
    }
    return compl_str; 
}

char* two_complement(char* binary_str, int len_compl){
    char* one_compl = one_complement(binary_str, len_compl);
    char* two_compl = add_in_base(one_compl, "1", 2);
    char* firstless_two_compl = malloc(len_compl + 1);
    firstless_two_compl[len_compl] = '\0';
    for (int i = len_compl - 1; i >= 0; i--){
        firstless_two_compl[i] = two_compl[i + 1];
    }
    free(one_compl);
    free(two_compl);
    return firstless_two_compl;
}


char* sub_binary(char* larger_binary, char* smaller_binary){
    int larger_len = strlen(larger_binary);
    char* two_compl = two_complement(smaller_binary, larger_len);
    char* compl_sum_str = add_in_base(two_compl, larger_binary, 2);
    int len_compl_sum_str = strlen(compl_sum_str);
    char* firstless_sum_str = malloc(len_compl_sum_str);
    firstless_sum_str[len_compl_sum_str - 1] = '\0';
    for (int i = len_compl_sum_str - 2; i >= 0; i--){
        firstless_sum_str[i] = compl_sum_str[i + 1];
    }
    return firstless_sum_str;
}
