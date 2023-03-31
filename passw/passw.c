#include <stdio.h>
#include <stdlib.h>

void handle_inp_err(FILE *stream, char *caller_name,
    char *err_msg) {
    fprintf(stream, "%s: %s\n", caller_name, err_msg);
}

void read_int(FILE* stream, int* result) {
    #define read_int_max_size 10
    char buffer[read_int_max_size] = {'\n'};
    for (; buffer[0] == '\n';) {
        if (fgets(buffer, read_int_max_size, stream) == 0)
            handle_inp_err(stream, "read_int", "unknown error");
    }
}

void take_input(FILE* stream, int *int_1, int *int_2) {
    fprintf(stream, "N-i gir: ");
    read_int(stdin, int_1);
    fprintf(stream, "M-i gir: ");
    read_int(stdin, int_2);
}

void passw(FILE *stream) {
    int n, m;
    take_input(stream, &n, &m);

}

#ifndef FOR_TESTING
int main() {
    int repeat_count = 3;
    int i;
    for (i = 0; i < repeat_count; ++i) passw(stdin);
    return 0;
}
#endif
