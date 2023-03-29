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
    int j = 0;
    for (; j < top; ++j) {
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

struct CompletionInfo {
    unsigned completed_count;
    unsigned completed_arr[3];
};

void print_freq_arr(struct CompletionInfo *freq_arr, int size) {
    int i;
    for (i = 0; i < size; ++i) {
        printf("(count: %u, %u%u%u)\n",
            freq_arr[i].completed_count,
            freq_arr[i].completed_arr[0],
            freq_arr[i].completed_arr[1],
            freq_arr[i].completed_arr[2]);
    } printf("\n");
}

void fill_freq_arr(struct CompletionInfo *freq_arr, int n, int m) {
    int common_value = rand() % n;
    freq_arr[common_value].completed_count = 3;
    int i;
    for (i = 0; i < 3 * m - 3; ++i) {
        int rand_index = rand() % n;
        for (; freq_arr[rand_index].completed_count >= 2;) {
            rand_index = rand() % n;
        }
        ++freq_arr[rand_index].completed_count;
    }
}

void fill_chains(struct LListNode **it_matrix,
    struct CompletionInfo *freq_arr, int n, int m) {
    int sizes[3] = {0, 0, 0};
    int i;
    for (i = 0; i < 3; ++i) {
        int rand_index = rand() % n;
        int rand_slot;
        do {
            for (; freq_arr[rand_index].completed_count == 0;) {
                rand_index = rand() % n;
            }
            rand_slot = rand() % 3;
            for (; freq_arr[rand_index].completed_arr[rand_slot] == 1;) {
                rand_slot = rand() % 3;
            } 
        } while(sizes[rand_slot] == 1);
        --freq_arr[rand_index].completed_count;
        freq_arr[rand_index].completed_arr[rand_slot] = 1;
        ++sizes[rand_slot];
        it_matrix[rand_slot]->value = rand_index + 1;
    }
    printf("heads: ");
    int j;
    for (j = 0; j < 3; ++j) {
        printf("%d ", it_matrix[j]->value);
    }
    printf("\nsizes: ");
    for (j = 0; j < 3; ++j) {
        printf("%d ", sizes[j]);
    } printf("\n");

    for (i = 0; i < 3 * m - 3; ++i) {
        int rand_index = rand() % n;
        int rand_slot;
        print_freq_arr(freq_arr, n);
        do {
            for (; freq_arr[rand_index].completed_count == 0;) {
                rand_index = rand() % n;
            }
            rand_slot = rand() % 3;
            for (; freq_arr[rand_index].completed_arr[rand_slot] == 1;) {
                rand_slot = rand() % 3;
            } 
        } while(sizes[rand_slot] == m);
        --freq_arr[rand_index].completed_count;
        freq_arr[rand_index].completed_arr[rand_slot] = 1;
        ++sizes[rand_slot];
        it_matrix[rand_slot]->next = malloc(sizeof(struct LListNode));
        it_matrix[rand_slot] = it_matrix[rand_slot]->next;
        it_matrix[rand_slot]->value = rand_index + 1;
    }
    print_freq_arr(freq_arr, n);
}

void generate_chains(struct LListNode *head_1,
    struct LListNode *head_2,    
    struct LListNode *head_3, int n, int m) {
    assert(head_1 != 0 && head_2 != 0 && head_3 != 0 &&
        "generate_chains: null pointer input");
    int it_matrix_size = 3;
    struct LListNode **it_matrix = malloc(
        it_matrix_size * sizeof(struct LListNode*));
    it_matrix[0] = head_1;
    it_matrix[1] = head_2;
    it_matrix[2] = head_3;

    int freq_arr_size = n;
    struct CompletionInfo *freq_arr = malloc(n * sizeof(struct CompletionInfo));
    int i;
    for (i = 0; i < freq_arr_size; ++i) {
        freq_arr[i].completed_count = 0;
        freq_arr[i].completed_arr[0] = 0;
        freq_arr[i].completed_arr[1] = 0;
        freq_arr[i].completed_arr[2] = 0;
    }
    fill_freq_arr(freq_arr, n, m);
    fill_chains(it_matrix, freq_arr, n, m);
    free(freq_arr); freq_arr = 0;

    for (i = 0; i < it_matrix_size; ++i) {
        assert(it_matrix[i] != 0 &&
            "generate_chains: illegal null pointer");
        it_matrix[i]->next = 0;
    }
    free(it_matrix); it_matrix = 0;
    print_chains(head_1, head_2, head_3, n, m);
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
    head_1->value = 0;
    head_2->value = 0;
    head_3->value = 0;
    generate_chains(head_1, head_2, head_3, n, m);
    print_chains(head_1, head_2, head_3, n, m);
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
