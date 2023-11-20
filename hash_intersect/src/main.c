#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printArr(int *arr, int len) {
    int i;
    for (i = 0; i < len; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int *makeHash(int *arr, int len, int m) {
    int *hash = malloc(m * sizeof(int));
    int i;
    if (!hash) {
        printf("malloc failed");
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < m; ++i) {
        hash[i] = -1;
    }
    for (i = 0; i < len; ++i) {
        int hash_idx;
        int j;
        hash_idx = arr[i] % m;
        // printf("makeHash: hash: \n\t");
        // printArr(hash, m);
        j = 0;
        while (j < m && hash[hash_idx] != -1) {
            hash_idx = (hash_idx + 1) % m;
            ++j;
        }
        if (j == m) {
            // printf("makeHash: j (%d) == m (%d)\n", j, m);
            free(hash);
            return NULL;
        }
        hash[hash_idx] = arr[i];
    }
    // printf("makeHash: hash: \n\t");
    // printArr(hash, m);
    return hash;
}

int searchHash(int *hash, int m, int val) {
    int hash_idx = val % m;
    int i = hash_idx;
    int j = 0;
    // printf("hash_idx: %d\n", hash_idx);
    while (j < m && hash[hash_idx] != val && hash[hash_idx] != -1) {
        ++j;
        hash_idx = (hash_idx + 1) % m;
        // printf("hash_idx: %d\n", hash_idx);
    }
    if (hash[hash_idx] == val) {
        return 1;
    }
    return 0;
}

int main() {
    int m = 11;
    int i;
    int a1[] = {3, 6, 2, 4, 1, 5};
    int a2[] = {7, 4, 3, 2, 8, 5};
    int n = sizeof(a1) / sizeof(a1[0]);
    int *hash = makeHash(a1, n, m);
    for (i = 0; i < n; ++i) {
        if (searchHash(hash, m, a2[i]) == 1) {
            printf("%d ", a2[i]);
        }
    }
    printf("\n");
    free(hash);
}
