#include <stdio.h>
#include <stdlib.h>

#define null 0

int searchSteps(int *dizi, int m, int index) {
    int steps, hash;
    printf("searchSteps: index: %d\n", index);
    hash = dizi[index] % m;
    if (index >= hash) {
        printf("searchSteps: index (%d) >= hash (%d)\n", index, hash);
        steps = index - hash + 1;
    } else {
        printf("searchSteps: index (%d) < hash (%d)\n", index, hash);
        steps = m - hash + index + 1;
    }
    printf("steps: %d\n", steps);
    printf("\n\n");
    return steps;
}

int main() {
    int m, *dizi, i, elementCount, totalSteps;
    scanf("%d", &m);
    elementCount = totalSteps = 0;
    dizi = (int *)calloc(m, sizeof(int));
    if (dizi == NULL) exit(-1);
    for (i = 0; i < m; ++i) {
        scanf("%d", &dizi[i]);
    }
    for (i = 0; i < m; i++) {
        if (dizi[i] != null) {
            elementCount++;
            totalSteps += searchSteps(dizi, m, i);
        }
    }
    printf("elementCount: %d\n", elementCount);
    printf("totalSteps: %d\n", totalSteps);
    printf("\nelemanlara ortalama %.2f adimda erisilir\n",
           totalSteps / (float)elementCount);

    free(dizi);
    return 0;
}
