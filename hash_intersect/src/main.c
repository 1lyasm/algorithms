#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int *makeHash(int *arr, int len, int m) {
    int *hash = malloc(m * sizeof(int)); int i;
    if (!hash) {
        printf("malloc failed");
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < m; ++i) {
        hash[i] = -1;
    }
    for (i = 0; i < len; ++i) {
        int hash_idx; int j;
        hash_idx = arr[i] % m;
        j = 0;
        while (j < m && hash[hash_idx] == -1) {
            hash_idx = (hash_idx + 1) % m;
            ++j;
        }
        if (j == m) {
            return NULL;
        }
        hash[hash_idx] = arr[i];
    }
    return hash;
}

int searchHash(int *hash, int m, int val) {
    int hash_idx = val % m;
    int i = hash_idx;
    int j = 0;
    while (j < m && hash[hash_idx] != val && hash[hash_idx] != -1) {
        ++j;
        hash_idx = (hash_idx + 1) % m;
    }
    if (j == m) {
        return 0;
    }
    if (hash[hash_idx] == -1) {
        return 0;
    }
    return 1;
}

int main() {
    printf("hi\n");
}

