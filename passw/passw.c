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
    struct LListNode *tail;
};

void print_list(struct LList *list) {
    assert(list->head != 0 && "print_list: empty list");
    struct LListNode *it = list->head;
    do {
        printf("%d ", it->val);
        it = it->next;
    } while (it != list->head);
    printf("\n");
}

void push_first_node(struct LList *list, int val) {
    list->head = malloc(sizeof(struct LListNode));
    list->head->val = val;
    list->head->next = list->head;
    list->tail = list->head;
}

void push_node(struct LList *list, int val) {
    if (list->head == 0) return push_first_node(list, val);
    list->tail->next = malloc(sizeof(struct LListNode));
    list->tail = list->tail->next;
    list->tail->val = val;
    list->tail->next = list->head;
}

int has_value(struct LList *list, int val) {
    struct LListNode *it = list->head;
    do {
        if (it->val == val) return 1;
        it = it->next;
    } while (it != list->head);
    return 0;
}

void del_list(struct LList *list) {
    struct LListNode *head_copy = list->head,
        *it = list->head, *next_it;
    do {
        next_it = it->next;
        free(it);
        it = 0;
        it = next_it;
    } while (it != head_copy);
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

void del_entry(struct UniqueRandGen *gen,
    int entry_idx) {
    gen->pool[entry_idx] = gen->pool[gen->pool_size - 1];
    --gen->pool_size;
}

void insert_entry(struct UniqueRandGen *gen, int val) {
    ++gen->pool_size;
    gen->pool[gen->pool_size - 1] = val;
}

void init_entries(struct UniqueRandGen *gen) {
    int i;
    for (i = 0; i < gen->pool_size; ++i)
        gen->pool[i] = i + 1;
}

void init_gen(struct UniqueRandGen *gen, int size) {
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
    del_entry(gen, entry_idx);
    return entry_val;
}

void restart_gen(struct UniqueRandGen *gen, int size) {
    gen->pool_size = size;
    init_entries(gen);
}

void fill_lists_but_last(struct LList *lists,
    int n_lists, int max_val, int list_size,
    int common, struct UniqueRandGen *gen) {
    int i;
    for (i = 0; i < n_lists - 1; ++i) {
        int j;
        for (j = 0; j < list_size - 1; ++j)
            push_node(&lists[i], generate(gen));
        restart_gen(gen, max_val);
        del_entry(gen, find_entry(gen, common));
    }
}

void fill_last_list(struct LList *lists, int list_size,
    struct UniqueRandGen *gen) {
    int i;
    for (i = 0; i < list_size - 1; ++i) {
        int rand_val = generate(gen);
        while (has_value(&lists[0], rand_val) == 1
            && has_value(&lists[1], rand_val) == 1) {
            insert_entry(gen, rand_val);
            rand_val = generate(gen);
        }
        push_node(&lists[list_size - 1], rand_val);
    }
}

void fill_lists(struct LList *lists, int n_lists,
    int max_val, int list_size, int common) {
    struct UniqueRandGen gen;
    init_gen(&gen, max_val);
    del_entry(&gen, find_entry(&gen, common));
    fill_lists_but_last(lists, n_lists,
        max_val, list_size, common, &gen);
    fill_last_list(lists, list_size, &gen);
    del_gen(&gen);
}

void print_lists(struct LList *lists, int n_lists) {
    int i;
    for (i = 0; i < n_lists; ++i) print_list(&lists[i]);
}

void fill_and_print(struct LList *lists,
    int n_lists, int common, int n, int m) {
    fill_lists(lists, n_lists, n, m, common);
    print_lists(lists, n_lists);
}

void del_lists(struct LList *lists, int n_lists) {
    int i;
    for (i = 0; i < n_lists; ++i) del_list(&lists[i]);
}

void passw() {
    long n, m;
    take_input(&n, &m);
    int common = gen_common(n);
    struct LList lists[3] = { {0} };
    int n_lists = sizeof(lists) / sizeof(lists[0]);
    fill_and_print(lists, n_lists, common, n, m);
    del_lists(lists, n_lists);
}

int main() {
    srand(time(0));
    passw();
}
