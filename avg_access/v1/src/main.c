#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M 24

int main() {
    {
        int null = (int)NULL;
        int hash[M] = {9, 7, 6,    null, null, 10,   13,   null,
                       4, 9, 7,    5,    6,    null, null, null,
                       1, 3, null, null, 6,    null, null, null};
        double avg = 0;
        int nOp = 0;
        int i;
        int j;
        int len = sizeof(hash) / sizeof(hash[0]);
        j = 0;
        for (i = 0; i < len; ++i) {
            if (hash[i] == null) {
                j = 0;
            } else {
                ++j;
            }
            nOp += j;
        }
        avg = nOp / (double)len;
        printf("avg: %lf\n", avg);
    }

    {
        int null = (int)NULL;
        int hash[M] = {0, 27, 40, 66, 17, 30, 43, 0, 0, 0, 0, 37, 0};
        double avg = 0;
        int nOp = 0;
        int i;
        int j;
        int len = sizeof(hash) / sizeof(hash[0]);
        j = 0;
        for (i = 0; i < len; ++i) {
            if (hash[i] == null) {
                j = 0;
            } else {
                ++j;
            }
            nOp += j;
        }
        avg = nOp / (double)len;
        printf("avg: %lf\n", avg);
    }
    return 0;
}
