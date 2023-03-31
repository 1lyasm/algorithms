#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define FOR_TESTING
#include "passw.c"

void assert_char_arr_eq(char *arr_1, char *arr_2,
    int count) {
    int i;
    for (i = 0; i < count; ++i)
        assert(arr_1[i] == arr_2[i]);
}

void print_char_arr(char *arr, int size) {
    int i;
    for (i = 0; i < size; ++i)
        printf("%c", arr[i]);
    printf("\n");
}

void test_handle_inp_err() {
    FILE* f = fopen("test.txt", "w");
    handle_inp_err(f, "test_handle_inp_err", "msg");
    fclose(f);
    f = fopen("test.txt", "r");
    char output[256];
    fread(output, sizeof(output[0]), 256, f);
    char expected[] = "test_handle_inp_err: msg\n";
    assert_char_arr_eq(output, expected, strlen(expected));
}

int main() {
    test_handle_inp_err();
    return 0;
}
