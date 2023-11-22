#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int val;
    int t_access;
} Pair;

typedef struct {
    Pair *pairs;
} ItemAccess;

int main() {
    int hash[] = {0, 27, 40, 66, 17, 30, 43, 0, 0, 0, 0, 37, 0};
    int m = sizeof(hash) / sizeof(hash[0]);
    int pairsLen = 0;
    int i;
    int j;
    ItemAccess *access = malloc(sizeof(ItemAccess));
    if (access == NULL) {
        printf("malloc failed\n");
        exit(EXIT_FAILURE);
    }
    access->pairs = malloc(sizeof(Pair) * m);
    if (access->pairs == NULL) {
        printf("malloc failed\n");
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < m; ++i) {
        if (hash[i] != 0) {
            int hashIdx = hash[i] % m;
            int steps;
            if (i >= hashIdx) {
                steps = i - hashIdx + 1;
            } else {
                steps = m - i + hashIdx + 1;
            }
            access->pairs[pairsLen].val = hash[i];
            access->pairs[pairsLen].t_access = steps;
            ++pairsLen;
        }
    }
    for (i = 0; i < pairsLen; ++i) {
        printf("val: %d, access steps: %d\n", access->pairs[i].val,
               access->pairs[i].t_access);
    }
    free(access->pairs);
    free(access);
    return 0;
}
