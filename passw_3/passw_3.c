#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct NM {
    int N;
    int M;
};

/* works only with positive ints */
int read_int() {
    int max_size = 10;
    char *s = malloc(max_size * sizeof(char));
    int top = 0;
    for (;;) {
        scanf("%c", &s[top]);
        if (s[top] == ' ' || s[top] == '\n') {
            if (top == 0) {
                continue;
            } else {
                break;
            }
        }
        ++top;
        if (top >= max_size) {
            free(s); s = 0;
            assert(!(top >= max_size) && "read_int: too large input");
            return -1;
        }
    }
    if (top < 1) {
        free(s); s = 0;
        assert(!(top < 1) && 
            "read_int: input int length must be greater than zero");
        return -1;
    }
    // int k = 0; 
    // for (; k < top; ++k) {
    //     printf("%c (k = %d)\n", s[k], k);
    // } printf("\n");
    int j = 0;
    for (; j < top; ++j) {
        // printf("hey, j = %d\n", j);
        if (s[j] - '0' < 0 || s[j] - '9' > 0) {
            // printf("\nhey, assert\n");
            free(s); s = 0;
            assert(1 == 0 &&
                "read_int: non-digit character entered");
            return -1;
        }
    }
    if (top > 1 && s[0] == '0') {
        free(s); s = 0;
        assert(1 == 0 && "read_int: int cannot start with zero");
        return -1;
    }
    int as_int = 0;
    int multiplier = 1;
    int i = top - 1;
    for (; i >= 0; --i) {
        as_int += multiplier * (s[i] - '0');
        multiplier *= 10;
    }
    if (as_int < 0) {
        free(s); s = 0;
        assert(!(as_int < 0) &&
            "read_int: something went wrong");
        return -1;
    }
    free(s); s = 0;
    printf("\ninput integer: %d\n", as_int);
    return as_int;
}

struct NM *read_input() {
    printf("N ve M-yi gir: ");
    int N, M;
    N = read_int();
    M = read_int();
    struct NM *nm = malloc(sizeof(struct NM));
    nm->N = N;
    nm->M = M;
    return nm;
}

void passw_3() {
    struct NM *nm = read_input();
    int N = nm->N;
    int M = nm->M;
    free(nm); nm = 0;
    // int *chain_1 = malloc(M * sizeof(int));
    // int *chain_2 = malloc(M * sizeof(int));
    // int *chain_3 = malloc(M * sizeof(int));
    // generate_common_number(N, M);
    // generate_chains(N, M);
    // find_common_number();
    // print_common_number();
    // find_displacements();
    // print_displacements();
    // rotate();
    // print_final_state();
    // free(chain_1); chain_1 = 0;
    // free(chain_2); chain_2 = 0;
    // free(chain_3); chain_3 = 0;
    return;
}

int main() {
    passw_3();
    passw_3();
    passw_3();
    return 0;
}
