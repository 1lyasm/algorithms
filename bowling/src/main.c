#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void printIntArray(int *arr, int n, char *msg) {
    int i;
    printf("%s: ", msg);
    for (i = 0; i < n; ++i) {
        printf("%d", arr[i]);
        if (i != n - 1) {
            printf(", ");
        }
    }
    printf("\n");
}

int main() {
    FILE *fp = fopen("input.txt", "r");
    int fLen;
    char *buffer;
    fseek(fp, 0, SEEK_END);
    fLen = ftell(fp);
    printf("fLen: %d\n", fLen);
    fseek(fp, 0, SEEK_SET);
    buffer = malloc((fLen + 1) * sizeof(char));
    buffer[fLen] = 0;
    fread(buffer, sizeof(char), fLen, fp);
    int i, j, k;
    int n;
    n = 0;
    printf("buffer: \"%s\"\n", buffer);
    for (i = 0; i < fLen; ++i) {
        if (buffer[i] == '\n') {
            ++n;
        }
    }
    printf("n: %d\n", n);
    int *pins = malloc(n * sizeof(int));
    k = 0;
    i = 0;
    while (i < fLen) {
        char *line = NULL;
        printf("hey\n");
        for (j = i; j < fLen; ++j) {
            if (buffer[j] == '\n') {
                break;
            }
        }
        line = malloc((j - i + 1) * sizeof(char));
        memcpy(line, &(buffer[i]), (j - i));
        line[j - i] = 0;
        printf("line: %s\n", line);
        pins[k] = atoi(line);
        printf("pins[%d]: %d\n", k, pins[k]);
        ++k;
        free(line);
        i = j + 1;
    }
    printf("pins: ");
    for (i = 0; i < n; ++i) {
        printf("%d ", pins[i]);
    }
    printf("\n");
    int *memo = malloc((n + 1) * sizeof(int));
    memset(memo, -1, n * sizeof(int));
    memo[n] = 0;
    for (i = n - 1; i >= 0; --i) {
        int maxVal = memo[i + 1];
        if (pins[i] > 0) {
            maxVal += pins[i];
        }
        if (i + 1 < n) {
            int cand = pins[i] * pins[i + 1] + memo[i + 2];
            if (cand > maxVal) {
                maxVal = cand;
            }
        }
        memo[i] = maxVal;
        printIntArray(memo, n, "memo");
    }
    printf("Maximum score is %d\n", memo[0]);
    free(buffer);
    free(pins);
    free(memo);
    return 0;
}

