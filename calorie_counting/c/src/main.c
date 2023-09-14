#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void fail(char *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(EXIT_FAILURE);
}

char *read_to_string(char *file_name) {
    int err;
    FILE *file = fopen(file_name, "r");
    if (!file) {
        fail("read_to_string: fopen failed");
    }
    err = fseek(file, 0, SEEK_END);
    if (err) {
        fail("read_to_string: fseek failed");
    }
    int len = ftell(file);
    if (len == -1L) {
        fail("read_to_string: ftell failed");
    }
    rewind(file);
    char *str = malloc((len + 1) * sizeof(char));
    if (!str) {
        fail("read_to_string: malloc failed");
    }
    str[len] = 0;
    int read_len = fread(str, sizeof(char), len, file);
    if (read_len != len) {
        fail("read_to_string: fread failed");
    }
    err = fclose(file);
    if (err) {
        fail("read_to_string: fclose failed");
    }
    return str;
}

int read_int(char *str, int *cur_index) {
    int number = 0, end = *cur_index, factor = 1;
    while (end >= 0 && str[end] != '\n') {
        number += factor * (str[end] - '0');
        factor *= 10;
        end -= 1;
    }
    *cur_index = end - 1;
    return number;
}

int sum_group(char *str, int *cur_index) {
    int sum = 0, end = *cur_index, number;
    while (end >= 0 && str[end] != '\n') {
        number = read_int(str, &end);
        sum += number;
    }
    *cur_index = end - 1;
    return sum;
}

int find_max_calories(char *str) {
    int cur_index = strlen(str) - 1, max_sum = -1, sum;
    while (cur_index >= 0) {
        sum = sum_group(str, &cur_index);
        if (sum > max_sum) {
            max_sum = sum;
        }
    }
    return max_sum;
}

int main(void) {
    char *str = read_to_string("src/input.txt");
    printf("%d\n", find_max_calories(str));
    free(str);
    return 0;
}
