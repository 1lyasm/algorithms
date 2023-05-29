#include <stdio.h>

#define MAX 50

void printMatrix(int mat[][3], int n) {
    int i = 0;
    for (i = 0; i < n; ++i)
        printf("(%c, %d, %d)\n", (char) mat[i][0], mat[i][1], mat[i][2]);
    printf("\n");
}

void fillMatrix(int mat[][3], int n) {
    int i = 0, j = 0;
    char work_code_char = 0;
    int work_code = 0;
    int isDuplicate = 0;
    int time = 0;
    int isValidTime = 1;
    for (i = 0; i < n; ++i) {
        printf("\n%d. Is kodu: ", i + 1);
        scanf(" %c", &work_code_char);
        work_code = (int) work_code_char;
        isDuplicate = 0;
        for (j = 0; j < i && !isDuplicate; ++j) {
            if (mat[j][0] == work_code) {
                printf("\nBu is kodu zaten var. Yenisini girin\n");
                --i;
                isDuplicate = 1;
            }
        }
        if (!isDuplicate)
            mat[i][0] = work_code;
    }
    printf("\n");
    for (i = 0; i < n; ++i) {
        printf("%c zamani: ",  (char) mat[i][0]);
        scanf("%d", &time);
        if (time < 1) {
            printf("\nZaman 1'den cok olmali, yeniden girin\n");
            --i;
        }
        else {
            mat[i][1] = time;
        }
    }
}

void schedule(int n, int head, int mat[][3]) {
    int currentWork = head;
    int nextWork = mat[currentWork][2];
    int i = 0;
    for (i = 0; i < mat[currentWork][1]; ++i)
        printf("%c ", (char)mat[currentWork][0]);
    while (nextWork != -1) {
        currentWork = nextWork;
        for (i = 0; i < mat[currentWork][1]; ++i)
            printf("%c ", (char) mat[currentWork][0]);
        nextWork = mat[currentWork][2];
    }
}

int main()
{
    int n = -1;
    int mat[MAX][3];
    int head = -1;
    int i = -1;
    int nextWorkIndex = -1;
    do {
        printf("Is sayisi: ");
        scanf("%d", &n);
    } while (n <= 0 && printf("\nHatali n, yeniden dene\n\n"));
    fillMatrix(mat, n);
    /*printMatrix(mat, n); */
    do {
        printf("\nhead: ");
        scanf("%d", &head);
    } while ((head < 0 || head > n - 1) && printf("\nHatali head, yeniden dene\n"));

    for (i = 0; i < n; ++i) {
        printf("%c-dan sonraki is: ", (char)mat[i][0]);
        scanf("%d", &nextWorkIndex);
        mat[i][2] = nextWorkIndex;
    }

    printf("OUTPUT: ");
    schedule(n, head, mat);

    printf("\n");
    return 0;
}

