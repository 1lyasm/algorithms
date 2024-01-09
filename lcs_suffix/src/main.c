#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *fp = fopen("input.txt", "r");
    int fLen;
    char *buf;
    char *a;
    char *b;
    int **memo;
    int i;
    int j;
    int aLen;
    int bLen;
    int lcsLen;

    fseek(fp, 0, SEEK_END);
    fLen = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    buf = malloc((fLen + 1) * sizeof(char));
    fread(buf, sizeof(char), fLen, fp);

    for (i = 0; i < fLen && buf[i] != '\n'; ++i);

    aLen = i;
    a = malloc((aLen + 1) * sizeof(char));
    a[aLen] = 0;
    memcpy(a, buf, aLen);

    bLen = fLen - i - 1;
    b = malloc((bLen + 1) * sizeof(char));
    b[bLen] = 0;
    memcpy(b, &(buf[i + 1]), bLen);

    memo = malloc((bLen + 1) * sizeof(int*));
    for (i = 0; i < bLen + 1; ++i) {
        memo[i] = calloc((aLen + 1), sizeof(int));
    }

    /* 'their' */
    /* 'habit' */

    for (i = bLen - 1; i >= 0; --i) {
        for (j = aLen - 1; j >= 0; --j) {
            if (b[i] == a[j]) {
                memo[i][j] = 1 + memo[i + 1][j + 1];
            } else {
                int passA = memo[i][j + 1];
                int passB = memo[i + 1][j];
                if (passA > passB) {
                    memo[i][j] = passA;
                } else {
                    memo[i][j] = passB;
                }
            }
        }
    }

    lcsLen = memo[0][0];
    printf("LCS length: %d\n", lcsLen);

    free(buf);
    free(a);
    free(b);

    for (i = 0; i < bLen + 1; ++i) {
        free(memo[i]);
    }
    free(memo);

    return 0;
}
