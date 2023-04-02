#include <stdio.h>
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
    if ((double) n < 1.5 * m - 0.5 || n <= 2 || m <= 2) return -1;
    return 0;
}

void take_input(long *n, long *m) {
    printf("N, M-i gir: ");
    char buf[256];
    do { fgets(buf, sizeof(buf), stdin);
    } while (buf[0] == '\n');
    if (do_conversion(n, m, buf) == -1) {
        printf("girdi okunamadi, yeniden dene\n");
        take_input(n, m);
    } else if (validate_input(*n, *m) == -1) {
        printf("yanlis girdi, yeniden dene\n");
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

struct LListNode* find(struct LList *list, int val) {
    struct LListNode *it = list->head;
    do {
        if (it->val == val) return it;
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
}

void del_entry(struct UniqueRandGen *gen,
    int entry_idx) {
    gen->pool[entry_idx] = gen->pool[gen->pool_size - 1];
    --gen->pool_size;
}

void init_entries(struct UniqueRandGen *gen) {
    int i;
    for (i = 0; i < gen->pool_size; ++i)
        gen->pool[i] = i + 1;
}

void init_gen(struct UniqueRandGen *gen, int size) {
    gen->pool_size = size;
    gen->pool = malloc(gen->pool_size * sizeof(int));
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

void del_gens(struct UniqueRandGen *gens, int n_lists) {
    int i;
    for (i = 0; i < n_lists; ++i) del_gen(&gens[i]);
}

void init_gens(struct UniqueRandGen *gens,
    int n_lists, int max_val) {
    int i;
    for (i = 0; i < n_lists; ++i) init_gen(&gens[i], max_val);
}

void del_entry_from_all(struct UniqueRandGen *gens,
    int n_lists, int common) {
    int i; 
    for (i = 0; i < n_lists; ++i)
        del_entry(&gens[i], find_entry(&gens[i], common));
} 

void fill_lists(struct LList *lists, int n_lists,
    int list_size, struct UniqueRandGen *gens) {
    int i;
    for (i = 0; i < n_lists; ++i) {
        int j;
        for (j = 0; j < list_size - 1; ++j)
            push_node(&lists[i], generate(&gens[i]));
    }
}

void remove_vertical_dup(struct LList *lists,
    struct LListNode **iters, int n_lists,
    struct UniqueRandGen *gens) {
    int i;
    for (i = 0; i < n_lists; ++i) {
        int rand_val, is_duplicate;
        do {
            rand_val = generate(&gens[i]);
            is_duplicate = find(&lists[(i + 1) % n_lists], rand_val) != 0 &&
                 find(&lists[(i + 2) % n_lists], rand_val) != 0;
        } while (is_duplicate == 1 && gens[i].pool_size != 0);
        if (is_duplicate == 0) {
            iters[i]->val = rand_val;
            return;
        }
    }
}

void remove_vertical_dups(struct LList *lists, int n_lists,
    struct UniqueRandGen *gens) {
    struct LListNode *it_0 = lists[0].head;
    do {
        struct LListNode *it_1 = find(&lists[1], it_0->val),
                         *it_2 = find(&lists[2], it_0->val);
        if (it_1 != 0 && it_2 != 0) {
            struct LListNode *iters[3] = {it_0, it_1, it_2};
            remove_vertical_dup(lists, iters, n_lists, gens);
        }
        it_0 = it_0->next;
    } while (it_0 != lists[0].head);
}

void print_lists(struct LList *lists, int n_lists) {
    int i;
    for (i = 0; i < n_lists; ++i) {
        printf("Chain %d: ", i);
        print_list(&lists[i]);
    }
}

void make_lists(struct LList *lists, int n_lists,
    int max_val, int list_size, int common) {
    struct UniqueRandGen gens[3];
    init_gens(gens, n_lists, max_val);
    del_entry_from_all(gens, n_lists, common);
    fill_lists(lists, n_lists, list_size, gens);
    remove_vertical_dups(lists, n_lists, gens);
    del_gens(gens, n_lists);
}

void make_and_print(struct LList *lists,
    int n_lists, int common, int n, int m) {
    make_lists(lists, n_lists, n, m, common);
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
    make_and_print(lists, n_lists, common, n, m);
    del_lists(lists, n_lists);
}

int main() {
    srand(time(0));
    passw();
}
