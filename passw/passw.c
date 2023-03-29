#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define true 1
#define false 0

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
        assert(top < max_size && "read_int: too large input");
    }
    assert(top >= 1 && 
            "read_int: input int length must be greater than zero");
    // int k = 0; 
    // for (; k < top; ++k) {
    //     printf("%c (k = %d)\n", s[k], k);
    // } printf("\n");
    int j = 0;
    for (; j < top; ++j) {
        // printf("hey, j = %d\n", j);
        assert(s[j] - '0' >= 0 && s[j] - '9' <= 0 &&
                "read_int: non-digit character entered");
    }
    if (top > 1) {
        assert(s[0] != '0' && 
            "read_int: int cannot  start with zero");
    }
    int as_int = 0;
    int multiplier = 1;
    int i = top - 1;
    for (; i >= 0; --i) {
        as_int += multiplier * (s[i] - '0');
        multiplier *= 10;
    }
    assert(as_int >= 0);
    free(s); s = 0;
    // printf("\ninput integer: %d\n", as_int);
    return as_int;
}

struct NM {
    int n;
    int m;
};

struct NM *read_input() {
    int n, m;
    printf("n-i gir: ");
    n = read_int();
    printf("m-i gir: ");
    m = read_int();
    unsigned less_than_3 = n < 3 || m < 3;
    unsigned n_not_bigger = n <= m;
    while (less_than_3 == true || n_not_bigger == true) {
        if (less_than_3 == true) {
            printf("N ve M ikiden cok olmali, ");
        } else if (n_not_bigger == true) {
            printf("N, M-den buyuk olmali, ");
        } else {
            assert(1 == 0 && "read_input: unreachable");
        }
        printf("n-i gir: ");
        n = read_int();
        printf("m-i gir: ");
        m = read_int();
        less_than_3 = n < 3 || m < 3;
        n_not_bigger = n <= m;
    }
    struct NM *nm = malloc(sizeof(struct NM));
    nm->n = n;
    nm->m = m;
    return nm;
}

struct LListNode {
    int value;
    struct LListNode *next;
};

struct LList {
    struct LListNode* head;
};

int is_duplicate(int rand_val, int current_index,
    int **gen_matrix, int gen_matrix_size) {
    int i;
    int result = 1;
    for (i = 0; i < gen_matrix_size; ++i) {
        if (i != current_index
            && gen_matrix[i][rand_val] == false) {
            result = 0;
            break;
        }
    }
    // printf("is_duplicate: returning %d\n", result);
    return result;
}

void print_matrix(int **matrix, int row_count,
    int column_count) {
    int i, j;
    for (i = 0; i < row_count; ++i) {
        for (j = 0; j < column_count; ++j) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void print_chains(struct LListNode *head_1, 
    struct LListNode *head_2,
    struct LListNode *head_3, int n, int m) {
    assert(head_1 != 0 && head_2 != 0 && head_3 != 0 &&
        "print_chains: null pointer input");
    int it_matrix_size = 3;
    struct LListNode **it_matrix = malloc(
        it_matrix_size * sizeof(struct LListNode*));
    it_matrix[0] = head_1;
    it_matrix[1] = head_2;
    it_matrix[2] = head_3;
    int i;
    for (i = 0; i < it_matrix_size; ++i) {
        printf("chain %d: ", i);
        for (; it_matrix[i] != 0;) {
            printf("%d ", it_matrix[i]->value);
            it_matrix[i] = it_matrix[i]->next;
        }
        printf("\n");
    }
    free(it_matrix); it_matrix = 0;
}

void generate_chains(struct LListNode *head_1,
    struct LListNode *head_2,    
    struct LListNode *head_3, int n, int m) {
    assert(head_1 != 0 && head_2 != 0 && head_3 != 0 &&
        "generate_chains: null pointer input");
    int gen_matrix_size = 3;
    int **gen_matrix = malloc(
        gen_matrix_size * sizeof(int*));
    int i;
    for (i = 0; i < gen_matrix_size; ++i) {
        gen_matrix[i] = calloc(n, sizeof(int));
    }
    int common = rand() % n;
    for (i = 0; i < gen_matrix_size; ++i) {
        gen_matrix[i][common] = true;
    }
    int it_matrix_size = 3;
    struct LListNode **it_matrix = malloc(
        it_matrix_size * sizeof(struct LListNode*));
    it_matrix[0] = head_1;
    it_matrix[1] = head_2;
    it_matrix[2] = head_3;
    for (i = 0; i < it_matrix_size; ++i) {
        assert(it_matrix[i] != 0 &&
            "generate_chains: illegal null pointer");
        it_matrix[i]->value = common + 1;
    }
    for (i = 0; i < m - 1; ++i) {
        int j;
        for (j = 0; j < gen_matrix_size; ++j) {
            int rand_value = rand() % n;
            for (; gen_matrix[j][rand_value] == true || 
                is_duplicate(rand_value, j,
                gen_matrix, gen_matrix_size) == true;) {
                // printf("\nhey\n");
                rand_value = rand() % n;
            }
            gen_matrix[j][rand_value] = true;
            print_matrix(gen_matrix, 3, n);
            assert(it_matrix[j] != 0 &&
                "generate_chains: illegal null pointer");
            it_matrix[j]->next = malloc(sizeof(struct LListNode));
            it_matrix[j] = it_matrix[j]->next;
            // printf("generate_chains: rand_value: %d\n", rand_value + 1);
            assert(rand_value + 1 >= 1 && rand_value + 1 <= n && 
                "generate_chains: value not in range");
            it_matrix[j]->value = rand_value + 1;
            // print_matrix(gen_matrix, 3, n);
        }
    }
    // printf("\nhey\n");
    for (i = 0; i < n; ++i) {
        if (i != common) {
            assert(!(gen_matrix[0][i] == true &&
                gen_matrix[1][i] == true &&
                gen_matrix[2][i] == true) &&
                "generate_chains: duplicate values");
        }
    }
    for (i = 0; i < gen_matrix_size; ++i) {
        free(gen_matrix[i]); gen_matrix[i] = 0;
    }
    free(gen_matrix); gen_matrix = 0;
    for (i = 0; i < it_matrix_size; ++i) {
        assert(it_matrix[i] != 0 &&
            "generate_chains: illegal null pointer");
        it_matrix[i]->next = 0;
    }
    int positions[3];
    int *used_positions = calloc(m, sizeof(int));
    for (i = 0; i < 3; ++i) {
        int random_temp = rand() % m;
        for (; used_positions[random_temp] == true;) {
            printf("generate_chains: in positions generator\n");
            random_temp = rand() % m;
        }
        used_positions[random_temp] = true;
        positions[i] = random_temp;
    }
    // printf("positions: ");
    // for (i = 0; i < 3; ++i) {
    //     printf("%d ", positions[i]);
    // }
    // printf("\n");
    free(used_positions); used_positions = 0;
    assert(positions[0] != positions[1] &&
        positions[0] != positions[2] &&
        positions[1] != positions[2] &&
        "generate_chains: common value in same common_indices");
    it_matrix[0] = head_1;
    it_matrix[1] = head_2;
    it_matrix[2] = head_3;
    for (i = 0; i < it_matrix_size; ++i) {
        int j;
        for (j = 0; j < positions[i]; ++j) {
            assert(it_matrix[i] != 0 &&
                "generate_chains: illegal null pointer");
            it_matrix[i] = it_matrix[i]->next;
        }
        assert(it_matrix[i] != 0 &&
            "generate_chains: illegal null pointer");
        struct LListNode *head_to_swap;
        if (i == 0) {
            head_to_swap = head_1;
        } else if (i == 1) {
            head_to_swap = head_2;
        } else if (i == 2) {
            head_to_swap = head_3;
        }
        assert(head_to_swap != 0 &&
            "generate_chains: illegal null pointer");
        int temp = head_to_swap->value;
        head_to_swap->value = it_matrix[i]->value;
        it_matrix[i]->value = temp;
    }
    int common_indices[3] = {0, 0, 0};
    it_matrix[0] = head_1;
    it_matrix[1] = head_2;
    it_matrix[2] = head_3;
    for (i = 0; i < it_matrix_size; ++i) {
        int j;
        for (j = 0; j < n; ++j) {
            assert(it_matrix[i] != 0 &&
                "generate_chains: illegal null pointer");
            if (it_matrix[i]->value == common + 1) {
                break;
            }
            it_matrix[i] = it_matrix[i]->next;
        }
        common_indices[i] = j;
        assert(j < n &&
            "generate_chains: common value could not be found in check");
    }
    free(it_matrix); it_matrix = 0;
    print_chains(head_1, head_2, head_3, n, m);
    assert(common_indices[0] != common_indices[1] &&
            common_indices[0] != common_indices[2] &&
            common_indices[1] != common_indices[2] &&
            "generate_chains: common value in same common_indices");
    printf("generate_chains: returning\n");
}

void free_chains(struct LListNode *head_1, 
    struct LListNode *head_2,
    struct LListNode *head_3, int n, int m) {
    assert(head_1 != 0 && head_2 != 0 && head_3 != 0 &&
        "free_chains: null pointer input");
    int it_matrix_size = 3;
    struct LListNode **it_matrix = malloc(
        it_matrix_size * sizeof(struct LListNode*));
    it_matrix[0] = head_1;
    it_matrix[1] = head_2;
    it_matrix[2] = head_3;
    int i;
    for (i = 0; i < it_matrix_size; ++i) {
        for (; it_matrix[i] != 0;) {
            struct LListNode *freed_ptr = it_matrix[i];
            struct LListNode *next_ptr = it_matrix[i]->next;
            free(freed_ptr); freed_ptr = 0;
            it_matrix[i] = next_ptr;
        }
    }
    free(it_matrix); it_matrix = 0;
}

void passw_3() {
    struct NM *nm = read_input();
    int n = nm->n;
    int m = nm->m;
    free(nm); nm = 0;
    struct LListNode *head_1 = malloc(sizeof(struct LListNode));
    struct LListNode *head_2 = malloc(sizeof(struct LListNode));
    struct LListNode *head_3 = malloc(sizeof(struct LListNode));
    generate_chains(head_1, head_2, head_3, n, m);
    print_chains(head_1, head_2, head_3, n, m);
    // find_common_number();
    // print_common_number();
    // find_displacements();
    // print_displacements();
    // rotate();
    // print_final_state();
    free_chains(head_1, head_2, head_3, n, m);
    return;
}

int main() {
    srand(time(0));
    passw_3();
    passw_3();
    passw_3();
    return 0;
}
