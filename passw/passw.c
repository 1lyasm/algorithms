#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <time.h>

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
        printf("girdi okunamadi, yeniden deneyin\n");
        take_input(n, m);
    } else if (validate_input(*n, *m) == -1) {
        printf("yanlis girdi, yeniden deneyin\n");
        take_input(n, m);
    }
}

int gen_common(long n) {
    return rand() % n + 1;
}

struct LListNode {
    int val;
    struct LListNode *next;
};

struct LList {
    struct LListNode *head;
};

void print_list(struct LList* list) {
    assert(list->head != 0 && "print_list: empty list");
    struct LListNode *it = list->head;
    do {
        printf("%d ", it->val);
        it = it->next;
    } while (it != list->head);
    printf("\n");
}

struct UniqueRandGen {
    int pool_size;
    int *pool;
};

int find_entry(struct UniqueRandGen *gen, int entry) {
    int i;
    for (i = 0; i < gen->pool_size; ++i) {
        if (gen->pool[i] == entry) return i;
    }
    assert(1 == 0 && 
        "find_entry: non-existent entry not allowed");
}

void del_entry_by_idx(struct UniqueRandGen *gen, 
    int entry_idx) {
    gen->pool[entry_idx] = gen->pool[gen->pool_size - 1];
    --gen->pool_size;
}

void init_entries(struct UniqueRandGen *gen) {
    int i;
    for (i = 0; i < gen->pool_size; ++i)
        gen->pool[i] = i + 1;
}

void init_gen(struct UniqueRandGen *gen,
    int size) {
    gen->pool_size = size;
    gen->pool = malloc(
        gen->pool_size * sizeof(int));
    init_entries(gen);
}

void del_gen(struct UniqueRandGen *gen) {
    free(gen->pool);
    gen->pool = 0;
}

int generate(struct UniqueRandGen *gen) {
    int entry_idx = rand() % gen->pool_size;
    int entry_val = gen->pool[entry_idx];
    del_entry_by_idx(gen, entry_idx);
    return entry_val;
}

void fill_and_print(struct LList *chains,
    int num_chains, int common, int n, int m) {
    struct UniqueRandGen gen;
    init_gen(&gen, n);
    fill_chains(chains, num_chains, m);
    del_gen(&gen);
}

void passw() {
    long n, m;
    take_input(&n, &m);
    int common = gen_common(n);
    struct LList chains[3];
    int num_chains = sizeof(chains) / sizeof(chains[0]);
    fill_and_print(chains, num_chains,
        common, n, m);
}

int main() {
    srand(time(0));
    passw();
}
