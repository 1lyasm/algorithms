#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

int do_conversion(long *val_1, long *val_2, char *buf) {
    char *end_ptr;
    *val_1 = strtol(buf, &end_ptr, 10);
    *val_2 = strtol(end_ptr, &end_ptr, 10);
    if (*val_1 == 0 || *val_2 == 0 ||
        errno == ERANGE) return -1;
    return 0;
}

int validate_input(long n, long m) {
    if (n <= m || n <= 0 || m <= 0) return -1;
    return 0;
}

void take_input(long *n, long *m) {
    printf("N, M-i gir: ");
    char buf[256];
    do { fgets(buf, sizeof(buf), stdin);
    } while (buf[0] == '\n');
    if (do_conversion(n, m, buf) == -1) {
        printf("error reading input, try again\n");
        take_input(n, m);
    } else if (validate_input(*n, *m) == -1) {
        printf("invalid input, try again\n");
        take_input(n, m);
    }
}

void passw() {
    long n, m;
    take_input(&n, &m);
}

int main() {
    passw();
}
