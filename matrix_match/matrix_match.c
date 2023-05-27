#include <stdio.h>
#include <stdlib.h>
#include <>

/*  */
struct Matrix {
    int **mat;
    int n;
};

/*  */
struct Matrix* buildMatrix(int n) {
    struct Matrix* mat = calloc(1, sizeof(struct Matrix));
    int i = 0;
    mat->mat = calloc(n, sizeof(int*));
    for (i = 0; i < n; ++i)
        mat->mat[i] = calloc(n, sizeof(int));
    mat->n = n;
    return mat;
}

/*  */
void freeMatrix(struct Matrix *mat) {
    int i = 0;
    for (i = 0; i < mat->n; ++i)
        free(mat->mat[i]);
    free(mat->mat);
    free(mat);
}

/* output: username read from stdin that must be freed */
char* takeUsername() {
    char *username = calloc(256, sizeof(char));
    printf("Enter username: ");
    scanf("%s", username);
    return username;
}

/*  */
void playAuto(struct Matrix *mat) {
    ;
}

/*  */
void playManual(struct Matrix* mat) {
    ;
}

/*  */
void play(struct Matrix* mat, int is_auto) {
    int i = 0, j = 0;
    for (i = 0; i < mat->n; ++i) {
        for (j = 0; j < mat->n; ++j)
            printf("%d ", mat->mat[i][j]);
        printf("\n");
    }
    if (is_auto == 1)
        playAuto(mat);
    else 
        playManual(mat);
    freeMatrix(mat);
}

/**/
int takeN() {
    int n = 0;
    printf("\nN: ");
    scanf("%d", &n);
    return n;
}

/**/
void makeRandom(struct Matrix* mat) {
    int poolSize = 2 * mat->n;
    int* pool = malloc(poolSize * sizeof(int));
    int i = 0;
    int randomIndex = 0, randomValue = 0;
    int xIndex = 0, yIndex = 0;
    for (i = 0; i < poolSize; ++i)
        pool[i] = i % (poolSize / 2) + 1;
    for (i = 0; i < poolSize; ++i) {
        randomIndex = rand() % poolSize;
        randomValue = pool[randomIndex];
        do {
            xIndex = rand() % mat->n;
            yIndex = rand() % mat->n;
        } while (mat->mat[xIndex][yIndex] != 0);
        mat->mat[xIndex][yIndex] = randomValue;
        pool[randomIndex] = pool[poolSize - 1];
        --poolSize;
    }
    free(pool);
}

/*  */
struct Matrix* makeMatrix(char makeMode) {
    int n = takeN();
    struct Matrix* mat = buildMatrix(n);
    if (makeMode == 'r')
        makeRandom(mat);
    else
        ;
    return mat;
}

/* */
void runGameMenu(char makeMode) {
    int choice = 0, isValid = 1;
    char* username = takeUsername();
    do {
        isValid = 1;
        printf("\nb. Oyun Menusu:\n\ti. Manuel Modda Oyna:\n\tii. Otomatik Modda Oyna:\n\tiii. Ana Menuye Don:\n\nSecim: ");
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            play(makeMatrix(makeMode), 0);
            break;
        case 2:
            play(makeMatrix(makeMode), 1);
            break;
        case 3:
            break;
        default:
            isValid = 0;
        }
    } while (isValid == 0 && printf("\n\nYanlis girdi, yeniden dene\n\n"));
    free(username);
}

/* */
void runMainMenu(void) {
    int choice = 0, isValid = 1;
    do {
        isValid = 1;
        printf("\na. Ana menu:\n\ti. Rastgele Matris Olustur:\n\tii. Dosyadan Matris Olustur:\n\tiii. Kullanicilarin Skorlarini Goster:\n\tiv. Cikis\n\nSecim: ");
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            runGameMenu('r');
            break;
        case 2:
            runGameMenu('f');
            break;
        case 3:
            break;
        case 4:
            exit(EXIT_SUCCESS);
        default:
            isValid = 0;
        }
    } while (isValid == 0 && printf("\n\nYanlis girdi, yeniden dene\n\n"));
}

int main(void)
{
    srand(time(0));
    while (1) runMainMenu();

    printf("\n");
    return 0;
}
