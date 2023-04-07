#include <stdio.h>
#include <stdlib.h>

int cmp_m(const void *a, const void *b) {
    int a0, a1, b0, b1;
    a0 = (*(const int**)a)[0];
    a1 = (*(const int**)a)[1];
    b0 = (*(const int**)b)[0];
    b1 = (*(const int**)b)[1];
    if ((a1 > b1) ||
        ((b1 == a1) && (a0 < b0))) { return -1;}
    return 1;
}

int cmp_i(const void* a, const void* b) {
    int arg1 = *((const int*) a), arg2 = *((const int*) b);
    if (arg1 > arg2) {return 1;}
    else if (arg1 < arg2) {return -1;}
    return 0;
}

struct Matrix {
    int** data;
    int nrow;
    int ncol;
};

int get_at(struct Matrix* this, int row, int col) {
    return (this->data)[row][col];
}

void set_at(struct Matrix* this, int row, int col, int val) {
    (this->data)[row][col] = val;
}

void __alloc_cols(struct Matrix* this, int i) {
    if (i >= this->nrow) {return;}
    this->data[i] = calloc(this->ncol, sizeof(int));
    __alloc_cols(this, ++i);
}

void __free_cols(struct Matrix* this, int i) {
    if (i >= this->nrow) {return;}
    free(this->data[i]);
    __free_cols(this, ++i);
}

void init(struct Matrix* this, int nrow, int ncol) {
    this->nrow = nrow;
    this->ncol = ncol;
    this->data = calloc(nrow, sizeof(int*));
    __alloc_cols(this, 0);
}

void del(struct Matrix* this) {
    __free_cols(this, 0);
    free(this->data);
}

void iprint(int* arr, int n, int i) {
    if (i >= n) {printf("\n"); return;}
    printf("%d ", arr[i]);
    iprint(arr, n, ++i);
}

void mprint(struct Matrix* this, int i) {
    if (i >= (this->nrow)) {printf("\n"); return;}
    iprint((this->data)[i], this->ncol, 0);
    mprint(this, ++i);
}

void inp(int* arr, int n, int i) {
    if (i >= n) {return;}
    scanf("%d", &arr[i]);
    inp(arr, n, ++i);
}

void fill_s(int* arr, int n, int* val_stack,
    int* freq_stack, int* sp, int i) {
    if (i >= n) {return;}
    if (i == 0) {val_stack[0] = arr[0]; freq_stack[0] = 1;}
    else if (val_stack[(*sp)] == arr[i]) {freq_stack[(*sp)]++;}
    else {(*sp)++; val_stack[(*sp)] = arr[i]; freq_stack[(*sp)] = 1;}
    fill_s(arr, n, val_stack, freq_stack, sp, ++i);
}

void fill_m(struct Matrix* m, int* val_stack,
    int* freq_stack, int* sp, int i) {
    if (i > (*sp)) {return;}
    m->data[i][0] = val_stack[i];
    m->data[i][1] = freq_stack[i];
    fill_m(m, val_stack, freq_stack, sp, ++i);
}

void groupSort(int* arr, int n, struct Matrix* m) {
    qsort(arr, n, sizeof(int), cmp_i);
    int val_stack[n], freq_stack[n], sp = 0;
    fill_s(arr, n, val_stack, freq_stack, &sp, 0);
    fill_m(m, val_stack, freq_stack, &sp, 0);
    qsort(m->data, sp + 1, sizeof(int*), cmp_m);
}

int main() {
    int n;
    scanf("%d", &n);
    int* arr = calloc(n, sizeof(int));
    inp(arr, n, 0);
    struct Matrix m;
    init(&m, n, 2);
    groupSort(arr, n, &m);
    printf("\n");
    mprint(&m, 0);
    del(&m);
    free(arr);
    printf("\n");
    return 0;
}
