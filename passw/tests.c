#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#define FOR_TESTING
#include "passw.c"

void test_read_int() {
    system("echo \"43\" > input.txt");
    int result;
    read_int(&result);
    assert(result = 43);

    system("cat input.txt");
    system("rm input.txt");
}

int main() {
    test_read_int();
    return 0;
}
