#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "q9.h"

void test_one_complement();
void test_two_complement();
void test_sub_binary();


int main(){
    test_one_complement();
    test_two_complement();
    test_sub_binary();
    return 0;
}

void test_one_complement(){
    printf("%s", "test_one_complement ... ");

    char* compl1 = one_complement("100", 8);
    assert(strcmp(compl1, "11111011") == 0);
    free(compl1);

    char* compl2 = one_complement("00", 3);
    assert(strcmp(compl2, "111") == 0);
    free(compl2);

    char* compl3 = one_complement("10001000", 8);
    assert(strcmp(compl3, "01110111") == 0);
    free(compl3);

    char* compl4 = one_complement("10000011", 8);
    assert(strcmp(compl4, "01111100") == 0);
    free(compl4);

    printf("%s", "OK\n");
    return;
}



void test_two_complement(){
    printf("%s", "test_two_complement ... ");

    char* compl1 = two_complement("100", 8);
    assert(strcmp(compl1, "11111100") == 0);
    free(compl1);

    char* compl2 = two_complement("00", 3);
    assert(strcmp(compl2, "000") == 0);
    free(compl2);

    char* compl3 = two_complement("00000", 5);
    assert(strcmp(compl3, "00000") == 0);
    free(compl3);

    char* compl4 = two_complement("101", 8);
    assert(strcmp(compl4, "11111011") == 0);
    free(compl4);

    printf("%s", "OK\n");
    return;
}

void test_sub_binary(){
    printf("%s", "test_sub_binary ... ");

    char* sub1 = sub_binary("10001000", "00000101");
    assert(strcmp(sub1, "10000011") == 0);
    free(sub1);

    char* sub2 = sub_binary("1010111111111", "1");
    assert(strcmp(sub2, "1010111111110") == 0);
    free(sub2);

    char* sub3 = sub_binary("11111", "0");
    assert(strcmp(sub3, "11111") == 0);
    free(sub3);

    char* sub4 = sub_binary("000", "0");
    assert(strcmp(sub4, "000") == 0);
    free(sub4);

    char* sub5 = sub_binary("10101010110111101000000111111111011001001100101100010101010101010100101100110101010101101111010000001111111110110010011001011000101010101010101001011001100110101010010110010101101010100101100101", "10101010110111101000000111111111011001001100101100010101010101010100101100110011010101001011001010");
    assert(strcmp(sub5, "10101010110111101000000111111111011001001100101100010101010101010100101100110101010101101111001101100101000111001010010001011001010001011101111101000100010001010101101001100010010101011010011011") == 0);
    free(sub5);

    char* sub6 = sub_binary("11111111", "11111111");
    assert(strcmp(sub6, "00000000") == 0);
    free(sub6);

    printf("%s", "OK\n");
    return;
}

