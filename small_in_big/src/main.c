#include <stdio.h>

int main() {
    int x;
    int y;
    int smaller;
    int bigger;
    int bigger_tmp;
    int isSmaller = 0;
    int isEq = 0;
    printf("Enter x: ");
    scanf(" %d", &x);
    printf("Enter y: ");
    scanf(" %d", &y);
    if (x < y) {
        smaller = x;
        bigger = y;
    } else {
        smaller = y;
        bigger = x;
    }
    bigger_tmp = bigger;
    do {
        if (bigger_tmp == smaller) {
            isEq = 1;
        } else if (bigger_tmp < smaller) {
            isSmaller = 1;
        }
        bigger_tmp /= 10;
    } while (!isSmaller && !isEq);
    if (isSmaller) {
        printf("%d sayisi %d sayisinin basinda gecmiyor.", smaller, bigger);
    } else {
        printf("%d sayisi %d sayisinin basinda geciyor.", smaller, bigger);
    }
    printf("\n");
}

