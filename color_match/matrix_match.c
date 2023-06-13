#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Matrix {
  int** mat;
  int n;
};

enum GameStatus { ONGOING, FAILURE, SUCCESS };

struct User {
  char username[64];
  int duration;
  int n;
  char makeMode;
  char playMode;
  int undoCount;
  enum GameStatus status;
  int score;
};

/*
 * in: matrix size
 * out: malloced matrix pointer
 */
struct Matrix* buildMatrix(int n) {
  struct Matrix* mat = calloc(1, sizeof(struct Matrix));
  int i = 0;
  mat->mat = calloc(n, sizeof(int*));
  for (i = 0; i < n; ++i) mat->mat[i] = calloc(n, sizeof(int));
  mat->n = n;
  return mat;
}

/*
 * in: matrix pointer
 * out: void after freeing
 */
void freeMatrix(struct Matrix* mat) {
  int i = 0;
  for (i = 0; i < mat->n; ++i) free(mat->mat[i]);
  free(mat->mat);
  free(mat);
}

/*
 * in: matrix pointer
 * out: void after pretty printing
 */
void printMatrix(struct Matrix* mat) {
  int i = 0, j = 0, k = 0;
  for (i = 0; i < mat->n; ++i) {
    printf("\n");
    for (k = 0; k < mat->n; ++k) printf("-------");
    printf("\n|");
    for (j = 0; j < mat->n; ++j) {
      if (mat->mat[i][j] != 0)
        printf("  %d   |", mat->mat[i][j]);
      else
        printf("      |");
    }
  }
  printf("\n");
  for (k = 0; k < mat->n; ++k) printf("-------");
  printf("\n\n");
}

/*
 * in: matrix pointer
 * out: game status after auto play (?)
 */
enum GameStatus playAuto(struct Matrix* mat, struct User *user) { return FAILURE; }

/*
 * in: Matrix pointer, n x 4 colorPositions matrix
 * out: void after finding colors and putting their positions to colorPositions
 */
void fillColorPositions(struct Matrix* mat, int (*colorPositions)[4]) {
  int i = 0, j = 0, isSecond = 0;
  for (i = 0; i < mat->n; ++i) {
    colorPositions[i][0] = -1;
    colorPositions[i][1] = -1;
    colorPositions[i][2] = -1;
    colorPositions[i][3] = -1;
  }
  for (i = 0; i < mat->n; ++i) {
    for (j = 0; j < mat->n; ++j) {
      if (mat->mat[i][j] > 0) {
        isSecond = 1;
        if (colorPositions[mat->mat[i][j] - 1][0] == -1) isSecond = 0;
        colorPositions[mat->mat[i][j] - 1][2 * isSecond] = i;
        colorPositions[mat->mat[i][j] - 1][2 * isSecond + 1] = j;
      }
    }
  }
}

/*
 * in: isConnectedArray: int pointer keeping if each color is already connected,
 * n: array size out: 1 if all are connected, 0 if not
 */
int checkIfAllConnected(int* isConnectedArray, int n) {
  int i = -1;
  int allConnected = 1;
  for (i = 0; i < n && allConnected; ++i)
    if (isConnectedArray[i] == 0) allConnected = 0;
  return allConnected;
}

/*
 * in: matrix pointer
 * out: 1 if all cells are filled, 0 if not
 */
int checkIfFull(struct Matrix* mat) {
  int i = -1, j = -1;
  int isFull = 1;
  for (i = 0; i < mat->n && isFull; ++i)
    for (j = 0; j < mat->n && isFull; ++j)
      if (mat->mat[i][j] == 0) isFull = 0;
  return isFull;
}

/*
 * in: Matrix pointer, x coord., y coord.
 * out: 1 if there is neighbor of same color to (x, y), 0 if not
 */
int checkIfHasSameNeighbor(struct Matrix* mat, int x, int y) {
  int color = mat->mat[x][y];
  return x >= 1 && mat->mat[x - 1][y] == color ||
         x <= mat->n - 2 && mat->mat[x + 1][y] == color ||
         y >= 1 && mat->mat[x][y - 1] == color ||
         y <= mat->n - 2 && mat->mat[x][y + 1] == color;
}

/*
* in: Matrix pointer, isConnectedArray: int pointer keeping if each color is
already connected
* out: if both sides have neighbor of same color, and that color is not
connected, that means they can be connected in future, detect if such color
exists and return 1, else 0
*/
int checkIfCanBeConnected(struct Matrix* mat, int* isConnectedArray,
                          int (*colorPositions)[4]) {
  int i = -1;
  int canBeConnected = 0;
  for (i = 0; i < mat->n && !canBeConnected; ++i)
    if (!isConnectedArray[i])
      if (checkIfHasSameNeighbor(mat, colorPositions[i][0],
                                 colorPositions[i][1]) &&
          checkIfHasSameNeighbor(mat, colorPositions[i][2],
                                 colorPositions[i][3]))
        canBeConnected = 1;
  return canBeConnected;
}

/*
 * in: Matrix pointer, isConnectedArray: int pointer keeping if each color is
 * already connected out: determine current game status and return it
 */
enum GameStatus getGameStatus(struct Matrix* mat, int* isConnectedArray,
                              int (*colorPositions)[4]) {
  int isFull = checkIfFull(mat);
  if (checkIfAllConnected(isConnectedArray, mat->n)) {
    if (isFull)
      return SUCCESS;
    else
      return FAILURE;
  } else {
    if (isFull) {
      if (checkIfCanBeConnected(mat, isConnectedArray, colorPositions))
        return ONGOING;
      else
        return FAILURE;
    } else
      return ONGOING;
  }
}

/*
 * in: two int pointers
 * out: void after mutate-swapping them
 */
void swapInts(int* i_1, int* i_2) {
  int temp = *i_1;
  *i_1 = *i_2;
  *i_2 = temp;
}

/*
 * in: Matrix pointer, (xSource, ySource) -> (xDest, yDest) showing move,
 * colorPositions: original positions of colors, isConnectedArray: connectivity
 * state of positions out: void after zeroing path between source and
 * destination
 */
void erasePath(struct Matrix* mat, int xSource, int ySource, int xDest,
               int yDest, int (*colorPositions)[4], int* isConnectedArray) {
  int color = mat->mat[xSource][ySource];
  if (isConnectedArray[color - 1]) isConnectedArray[color - 1] = 0;
  if (xSource == xDest) {
    int y;
    if (ySource > yDest) swapInts(&ySource, &yDest);
    for (y = ySource; y <= yDest; ++y) {
      if (!((xSource == colorPositions[color - 1][0] &&
             y == colorPositions[color - 1][1]) ||
            (xSource == colorPositions[color - 1][2] &&
             y == colorPositions[color - 1][3])))
        mat->mat[xSource][y] = 0;
    }
  } else {
    int x;
    if (xSource > xDest) swapInts(&xSource, &xDest);
    for (x = xSource; x <= xDest; ++x) {
      if (!((x == colorPositions[color - 1][0] &&
             ySource == colorPositions[color - 1][1]) ||
            (x == colorPositions[color - 1][2] &&
             ySource == colorPositions[color - 1][3])))
        mat->mat[x][ySource] = 0;
    }
  }
}

/*
 * in: undoMatrix: 5x4 undo matrix, undoCount, move information
 * out: void after pushing the move to undoMatrix
 */
void addToUndoMatrix(int undoMatrix[][4], int* undoCount, int xSource,
                     int ySource, int xDest, int yDest) {
  if (*undoCount == 5) {
    int i = -1, j = -1;
    for (i = 0; i <= 3; ++i)
      for (j = 0; j < 4; ++j) undoMatrix[i][j] = undoMatrix[i + 1][j];
    --(*undoCount);
  }
  undoMatrix[*undoCount][0] = xSource;
  undoMatrix[*undoCount][1] = ySource;
  undoMatrix[*undoCount][2] = xDest;
  undoMatrix[*undoCount][3] = yDest;
  ++(*undoCount);
}

/*
 * in: Matrix pointer
 * out: game status: either FAILURE or SUCCESS
 */
enum GameStatus playManual(struct Matrix* mat, struct User *user) {
  int stepCounter = 1;
  int(*colorPositions)[4] = malloc(mat->n * sizeof(int[4]));
  int* isConnectedArray = calloc(mat->n, sizeof(int));
  enum GameStatus gameStatus = ONGOING;
  int undoMatrix[5][4];
  int undoCount = 0;
  fillColorPositions(mat, colorPositions);
  while (gameStatus == ONGOING) {
    int xSource = -1, ySource = -1, xDestination = -1, yDestination = -1;
    int color = -1;
    int connectedColor = 0;
    char undoResponse = 'y';
    while (undoCount >= 1 && undoResponse == 'y') {
      printf("Undo [y/n]? ");
      scanf(" %c", &undoResponse);
      printf("\n");
      if (undoResponse == 'y') {
        ++user->undoCount;
        erasePath(mat, undoMatrix[undoCount - 1][0],
                  undoMatrix[undoCount - 1][1], undoMatrix[undoCount - 1][2],
                  undoMatrix[undoCount - 1][3], colorPositions,
                  isConnectedArray);
        printMatrix(mat);
        --undoCount;
        --stepCounter;
      }
    }
    printf("%d. ADIM:\n\tSource: ", stepCounter);
    scanf("%d, %d", &xSource, &ySource);
    printf("\tDestination: ");
    scanf("%d, %d", &xDestination, &yDestination);
    printf("\n");
    if (xSource < 0 || xSource >= mat->n || ySource < 0 || ySource >= mat->n ||
        xDestination < 0 || xDestination >= mat->n || yDestination < 0 ||
        yDestination >= mat->n || mat->mat[xSource][ySource] == 0 ||
        (xSource == xDestination) + (ySource == yDestination) != 1) {
      printf("Gecersiz hamle, yeniden dene\n");
      --stepCounter;
    } else {
      color = mat->mat[xSource][ySource];
      int pathIsEmpty = 1;
      int colorXSource = colorPositions[color - 1][0];
      int colorYSource = colorPositions[color - 1][1];
      int colorXDestination = colorPositions[color - 1][2];
      int colorYDestination = colorPositions[color - 1][3];
      int x = -1, y = -1;
      if (xSource == xDestination) {
        int direction = 1 - 2 * (ySource > yDestination);
        int yUpper = (ySource > yDestination) ? ySource : yDestination;
        int yLower = (ySource > yDestination) ? yDestination : ySource;
        y = ySource + direction;
        while (pathIsEmpty && (y >= yLower && y <= yUpper)) {
          if (mat->mat[xSource][y] != 0) pathIsEmpty = 0;
          if (pathIsEmpty) y += direction;
        }
        connectedColor =
            (y == yDestination && (yDestination == colorYSource ||
                                   yDestination == colorYDestination));
        if (!pathIsEmpty && !connectedColor) {
          printf("Gecersiz hamle, yeniden dene\n");
          --stepCounter;
        } else {
          if (connectedColor) {
            isConnectedArray[color - 1] = 1;
            printf("\nSayilar eslestirildi\n");
          }
          addToUndoMatrix(undoMatrix, &undoCount, xSource, ySource,
                          xDestination, yDestination);
          for (y = ySource; (y >= yLower && y <= yUpper); y += direction)
            mat->mat[xSource][y] = color;
        }
      } else {
        int direction = 1 - 2 * (xSource > xDestination);
        int xUpper = (xSource > xDestination) ? xSource : xDestination;
        int xLower = (xSource > xDestination) ? xDestination : xSource;
        x = xSource + direction;
        while (pathIsEmpty && (x >= xLower && x <= xUpper)) {
          if (mat->mat[x][ySource] != 0) pathIsEmpty = 0;
          if (pathIsEmpty) x += direction;
        }
        connectedColor =
            x == xDestination &&
            (xDestination == colorXSource || xDestination == colorXDestination);
        if (!pathIsEmpty && !connectedColor) {
          printf("Gecersiz hamle, yeniden dene\n");
          --stepCounter;
        } else {
          if (connectedColor) {
            isConnectedArray[color - 1] = 1;
            printf("\nSayilar eslestirildi\n");
          }
          addToUndoMatrix(undoMatrix, &undoCount, xSource, ySource,
                          xDestination, yDestination);
          for (x = xSource; (x >= xLower && x <= xUpper); x += direction)
            mat->mat[x][ySource] = color;
        }
      }
    }
    printMatrix(mat);
    ++stepCounter;
    gameStatus = getGameStatus(mat, isConnectedArray, colorPositions);
  }
  if (gameStatus == SUCCESS)
    printf("\nKazandiniz\n");
  else if (gameStatus == FAILURE)
    printf("\nKaybettiniz\n");
  free(colorPositions);
  free(isConnectedArray);
  return gameStatus;
}

/*
 * in: user pointer
 * out: void after pretty printing user game info
 */
void printGameInfo(struct User* user) {
  printf(
      "\tAd: %s\n\tOynama zamani: %d:%d\n\tMatris boyutu: %d x %d\n\tOlusturma "
      "sekli: %s\n\tOynama sekli: %s\n\tUndo sayisi: %d\n\tSkor: %d\n\tSonuc: "
      "%s\n\n",
      user->username, user->duration / 60, user->duration % 60, user->n,
      user->n, user->makeMode == 'r' ? "random" : "dosya",
      user->playMode == 'a' ? "auto" : "manuel", user->undoCount, user->score,
      user->status == SUCCESS ? "kazandi" : "kaybetti");
}

/*
 * in: user pointer
 * out: void after computing and setting score field
 */
void computeScore(struct User* user) {
  if (user->status == FAILURE) {
    user->score = 0;
    return;
  }
  double nWeight = user->playMode == 'a' ? 0.93 : 1;
  double durationWeight = user->playMode == 'a' ? 0.1 : 0.005;
  double undoCountWeight = user->playMode == 'a' ? 0.0000005 : 0.001;
  double score = nWeight * user->n - durationWeight * user->duration -
                 undoCountWeight * user->undoCount;
  score = 100 - pow(2, -score) * 100;
  user->score = score > 0 ? score : 0;
}

/*
 * in:
 * out: void after creating user with auto playMode and running computeScore and
 * printing results
 */
void testComputeScoreAuto() {
  struct User u;
  u.playMode = 'a';
  {
    u.n = 5;
    u.duration = 40;
    u.undoCount = 1;
    u.status = SUCCESS;
    computeScore(&u);
    printf("(n: %d, dur: %d, undo: %d, status: %d) -> %d\n\n", u.n, u.duration,
           u.undoCount, u.status, u.score);
  }
  {
    u.n = 15;
    u.duration = 40;
    u.undoCount = 1;
    u.status = SUCCESS;
    computeScore(&u);
    printf("(n: %d, dur: %d, undo: %d, status: %d) -> %d\n\n", u.n, u.duration,
           u.undoCount, u.status, u.score);
  }
  {
    u.n = 7;
    u.duration = 1;
    u.undoCount = 300000;
    u.status = SUCCESS;
    computeScore(&u);
    printf("(n: %d, dur: %d, undo: %d, status: %d) -> %d\n\n", u.n, u.duration,
           u.undoCount, u.status, u.score);
  }
  {
    u.n = 7;
    u.duration = 340;
    u.undoCount = 300000;
    u.status = SUCCESS;
    computeScore(&u);
    printf("(n: %d, dur: %d, undo: %d, status: %d) -> %d\n\n", u.n, u.duration,
           u.undoCount, u.status, u.score);
  }
  {
    u.n = 7;
    u.duration = 10;
    u.undoCount = 300000;
    u.status = SUCCESS;
    computeScore(&u);
    printf("(n: %d, dur: %d, undo: %d, status: %d) -> %d\n\n", u.n, u.duration,
           u.undoCount, u.status, u.score);
  }
  {
    u.n = 7;
    u.duration = 1;
    u.undoCount = 600000;
    u.status = SUCCESS;
    computeScore(&u);
    printf("(n: %d, dur: %d, undo: %d, status: %d) -> %d\n\n", u.n, u.duration,
           u.undoCount, u.status, u.score);
  }
  {
    u.n = 777;
    u.duration = 0.1;
    u.undoCount = 1;
    u.status = FAILURE;
    computeScore(&u);
    printf("(n: %d, dur: %d, undo: %d, status: %d) -> %d\n\n", u.n, u.duration,
           u.undoCount, u.status, u.score);
  }
  {
    u.n = 3;
    u.duration = 1;
    u.undoCount = 3;
    u.status = SUCCESS;
    computeScore(&u);
    printf("(n: %d, dur: %d, undo: %d, status: %d) -> %d\n\n", u.n, u.duration,
           u.undoCount, u.status, u.score);
  }
  {
    u.n = 30;
    u.duration = 10;
    u.undoCount = 3000000;
    u.status = SUCCESS;
    computeScore(&u);
    printf("(n: %d, dur: %d, undo: %d, status: %d) -> %d\n\n", u.n, u.duration,
           u.undoCount, u.status, u.score);
  }
  {
    u.n = 30;
    u.duration = 1000;
    u.undoCount = 3000000;
    u.status = SUCCESS;
    computeScore(&u);
    printf("(n: %d, dur: %d, undo: %d, status: %d) -> %d\n\n", u.n, u.duration,
           u.undoCount, u.status, u.score);
  }
  {
    u.n = 30;
    u.duration = 100;
    u.undoCount = 3000000;
    u.status = SUCCESS;
    computeScore(&u);
    printf("(n: %d, dur: %d, undo: %d, status: %d) -> %d\n\n", u.n, u.duration,
           u.undoCount, u.status, u.score);
  }
  {
    u.n = 30;
    u.duration = 100;
    u.undoCount = 30000000;
    u.status = SUCCESS;
    computeScore(&u);
    printf("(n: %d, dur: %d, undo: %d, status: %d) -> %d\n\n", u.n, u.duration,
           u.undoCount, u.status, u.score);
  }
  {
    u.n = 30;
    u.duration = 100;
    u.undoCount = 300000000;
    u.status = SUCCESS;
    computeScore(&u);
    printf("(n: %d, dur: %d, undo: %d, status: %d) -> %d\n\n", u.n, u.duration,
           u.undoCount, u.status, u.score);
  }
}

/*
 * in:
 * out: void after creating user with manual playMode and running computeScore
 * and printing results
 */
void testComputeScoreManual() {
  struct User u;
  u.playMode = 'm';
  {
    u.n = 2;
    u.duration = 3;
    u.undoCount = 0;
    u.status = SUCCESS;
    computeScore(&u);
    printf("(n: %d, dur: %d, undo: %d, status: %d) -> %d\n\n", u.n, u.duration,
           u.undoCount, u.status, u.score);
  }
  {
    u.n = 2;
    u.duration = 3;
    u.undoCount = 0;
    u.status = FAILURE;
    computeScore(&u);
    printf("(n: %d, dur: %d, undo: %d, status: %d) -> %d\n\n", u.n, u.duration,
           u.undoCount, u.status, u.score);
  }
  {
    u.n = 2;
    u.duration = 3;
    u.undoCount = 2;
    u.status = SUCCESS;
    computeScore(&u);
    printf("(n: %d, dur: %d, undo: %d, status: %d) -> %d\n\n", u.n, u.duration,
           u.undoCount, u.status, u.score);
  }
  {
    u.n = 2;
    u.duration = 7;
    u.undoCount = 0;
    u.status = SUCCESS;
    computeScore(&u);
    printf("(n: %d, dur: %d, undo: %d, status: %d) -> %d\n\n", u.n, u.duration,
           u.undoCount, u.status, u.score);
  }
  {
    u.n = 3;
    u.duration = 7;
    u.undoCount = 0;
    u.status = SUCCESS;
    computeScore(&u);
    printf("(n: %d, dur: %d, undo: %d, status: %d) -> %d\n\n", u.n, u.duration,
           u.undoCount, u.status, u.score);
  }
  {
    u.n = 2;
    u.duration = 3;
    u.undoCount = 3;
    u.status = FAILURE;
    computeScore(&u);
    printf("(n: %d, dur: %d, undo: %d, status: %d) -> %d\n\n", u.n, u.duration,
           u.undoCount, u.status, u.score);
  }
  {
    u.n = 3;
    u.duration = 15;
    u.undoCount = 0;
    u.status = SUCCESS;
    computeScore(&u);
    printf("(n: %d, dur: %d, undo: %d, status: %d) -> %d\n\n", u.n, u.duration,
           u.undoCount, u.status, u.score);
  }
  {
    u.n = 3;
    u.duration = 150;
    u.undoCount = 0;
    u.status = SUCCESS;
    computeScore(&u);
    printf("(n: %d, dur: %d, undo: %d, status: %d) -> %d\n\n", u.n, u.duration,
           u.undoCount, u.status, u.score);
  }
  {
    u.n = 3;
    u.duration = 1500;
    u.undoCount = 0;
    u.status = SUCCESS;
    computeScore(&u);
    printf("(n: %d, dur: %d, undo: %d, status: %d) -> %d\n\n", u.n, u.duration,
           u.undoCount, u.status, u.score);
  }
  {
    u.n = 5;
    u.duration = 120;
    u.undoCount = 10;
    u.status = SUCCESS;
    computeScore(&u);
    printf("(n: %d, dur: %d, undo: %d, status: %d) -> %d\n\n", u.n, u.duration,
           u.undoCount, u.status, u.score);
  }
  {
    u.n = 7;
    u.duration = 120;
    u.undoCount = 10;
    u.status = SUCCESS;
    computeScore(&u);
    printf("(n: %d, dur: %d, undo: %d, status: %d) -> %d\n\n", u.n, u.duration,
           u.undoCount, u.status, u.score);
  }
  {
    u.n = 7;
    u.duration = 120;
    u.undoCount = 100;
    u.status = SUCCESS;
    computeScore(&u);
    printf("(n: %d, dur: %d, undo: %d, status: %d) -> %d\n\n", u.n, u.duration,
           u.undoCount, u.status, u.score);
  }
  {
    u.n = 7;
    u.duration = 3600;
    u.undoCount = 1000;
    u.status = SUCCESS;
    computeScore(&u);
    printf("(n: %d, dur: %d, undo: %d, status: %d) -> %d\n\n", u.n, u.duration,
           u.undoCount, u.status, u.score);
  }
  {
    u.n = 11;
    u.duration = 360;
    u.undoCount = 100;
    u.status = SUCCESS;
    computeScore(&u);
    printf("(n: %d, dur: %d, undo: %d, status: %d) -> %d\n\n", u.n, u.duration,
           u.undoCount, u.status, u.score);
  }
  {
    u.n = 11;
    u.duration = 1800;
    u.undoCount = 100;
    u.status = SUCCESS;
    computeScore(&u);
    printf("(n: %d, dur: %d, undo: %d, status: %d) -> %d\n\n", u.n, u.duration,
           u.undoCount, u.status, u.score);
  }
  {
    u.n = 11;
    u.duration = 360;
    u.undoCount = 6000;
    u.status = SUCCESS;
    computeScore(&u);
    printf("(n: %d, dur: %d, undo: %d, status: %d) -> %d\n\n", u.n, u.duration,
           u.undoCount, u.status, u.score);
  }
  {
    u.n = 15;
    u.duration = 1800;
    u.undoCount = 100;
    u.status = SUCCESS;
    computeScore(&u);
    printf("(n: %d, dur: %d, undo: %d, status: %d) -> %d\n\n", u.n, u.duration,
           u.undoCount, u.status, u.score);
  }
}

/*
 * in: Matrix pointer, is_auto: 1 if auto else 0, username: username string,
 * users: array of user pointers, m: users length, makeMode: 'r' if random, 'f'
 * if file out: void after creating and pushing a user to users and calling
 * corresponding play... function
 */
void play(struct Matrix* mat, int is_auto, char* username, struct User** users,
          int* m, char makeMode) {
  int i = -1;
  time_t startTime;
  users[(*m)++] = malloc(sizeof(struct User));
  for (i = 0; i < 64; ++i) users[*m - 1]->username[i] = username[i];
  users[*m - 1]->playMode = is_auto ? 'a' : 'm';
  users[*m - 1]->makeMode = makeMode;
  users[*m - 1]->n = mat->n;
  users[*m - 1]->undoCount = 0;
  startTime = time(0);
  if (is_auto == 1)
    users[*m - 1]->status = playAuto(mat, users[*m - 1]);
  else
    users[*m - 1]->status = playManual(mat, users[*m - 1]);
  users[*m - 1]->duration = time(0) - startTime;
  computeScore(users[*m - 1]);
  freeMatrix(mat);
  printf("\nOyun bilgisi:\n");
  printGameInfo(users[*m - 1]);
}

/*
 * in:
 * out: int taken from stdin
 */
int takeN() {
  int n = 0;
  printf("\nN: ");
  scanf("%d", &n);
  return n;
}

/*
 * in:
 * out: void after printing
 */
void printIntArray(int* array, int size) {
  int i = 0;
  for (i = 0; i < size; ++i) printf("%d ", array[i]);
  printf("\n");
}

/*
 * in: Matrix pointer
 * out: void after randomly filling the matrix pointed by mat
 */
void makeRandom(struct Matrix* mat) {
  int poolSize = 2 * mat->n;
  int* pool = malloc(poolSize * sizeof(int));
  int i = 0;
  int randomIndex = 0, randomValue = 0;
  int xIndex = 0, yIndex = 0;
  for (i = 0; i < poolSize; ++i) pool[i] = i % (poolSize / 2) + 1;
  for (i = 0; i < 2 * mat->n; ++i) {
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

/*
 * in: Matrix pointer
 * out: void after filling the matrix pointed by mat from file
 */
void makeFromFile(struct Matrix* mat) {
  char fileName[20] = {0};
  int i, j, temp;
  FILE* data;
  printf("Dosya Adini Giriniz: ");
  scanf("%s", fileName);
  data = fopen(fileName, "r");
  if (!data) {
    printf("Dosya Acilamadi!");
    exit(EXIT_FAILURE);
  }
  while (!feof(data)) {
    fscanf(data, "%d %d %d\n", &i, &j, &temp);
    mat->mat[i][j] = temp;
  }
  fclose(data);
}

/*
 * in: makeMode: random or file
 * out: matrix pointer after building and filling it
 */
struct Matrix* makeMatrix(char makeMode) {
  int n = takeN();
  struct Matrix* mat = buildMatrix(n);
  if (makeMode == 'r')
    makeRandom(mat);
  else
    makeFromFile(mat);
  printf("Matris: \n");
  printMatrix(mat);
  return mat;
}

/*
 * in: makeMode: matrix generation mode, users: user array to be pushed to, m:
 * user size out: void after running games and user wants to go to main menu
 */
void runGameMenu(char makeMode, struct User** users, int* m) {
  int choice = 0, isValid = 1;
  char username[64] = {0};
  printf("Kullanici adi: ");
  scanf("%s", username);
  do {
    isValid = 1;
    printf(
        "\nb. Oyun Menusu:\n\ti. Manuel Modda Oyna:\n\tii. Otomatik Modda "
        "Oyna:\n\tiii. Ana Menuye Don:\n\nSecim: ");
    scanf("%d", &choice);
    switch (choice) {
      case 1:
        play(makeMatrix(makeMode), 0, username, users, m, makeMode);
        break;
      case 2:
        play(makeMatrix(makeMode), 1, username, users, m, makeMode);
        break;
      case 3:
        break;
      default:
        isValid = 0;
    }
  } while (isValid == 0 && printf("\n\nYanlis girdi, yeniden dene\n\n"));
}

/*
 * in: users, m: user count
 * out: void after freeing user pointers in users
 */
void freeUsers(struct User** users, int* m) {
  int i = -1;
  for (i = 0; i < *m; ++i) free(users[i]);
}

/*
 * in: users, m: user count
 * out: void after grouping scores by usernames and printing them together for
 * all usernames
 */
void printUserScores(struct User** users, int* m) {
  int i = -1, j = -1;
  int* visitedArray = calloc(*m, sizeof(int));
  char* currentUsername = malloc(64 * sizeof(char));
  int gameCount = -1;
  printf("\n\n");
  for (i = 0; i < *m; ++i) {
    if (!visitedArray[i]) {
      gameCount = 0;
      memcpy(currentUsername, users[i]->username, 64);
      printf("%s-nin skorlari:\n", users[i]->username);
      for (j = i; j < *m; ++j) {
        if (strcmp(currentUsername, users[j]->username) == 0) {
          visitedArray[j] = 1;
          printGameInfo(users[j]);
          ++gameCount;
        }
      }
      printf("\n%s %d oyun oynadi\n\n", currentUsername, gameCount);
    }
  }
  free(visitedArray);
  free(currentUsername);
}

/*
 * in: users, m: user count
 * out: void after responding to options until user wants to quit
 */
void runMainMenu(struct User** users, int* m) {
  int choice = 0, isValid = 1;
  do {
    isValid = 1;
    printf(
        "\na. Ana menu:\n\ti. Rastgele Matris Olustur:\n\tii. Dosyadan Matris "
        "Olustur:\n\tiii. Kullanicilarin Skorlarini Goster:\n\tiv. "
        "Cikis\n\nSecim: ");
    scanf("%d", &choice);
    switch (choice) {
      case 1:
        runGameMenu('r', users, m);
        break;
      case 2:
        runGameMenu('f', users, m);
        break;
      case 3:
        printUserScores(users, m);
        break;
      case 4:
        freeUsers(users, m);
        exit(EXIT_SUCCESS);
      default:
        isValid = 0;
    }
  } while (isValid == 0 && printf("\n\nYanlis girdi, yeniden dene\n\n"));
}

/*
 * 1. show outputs of calculateScore() for example cases,
 * 2. run infinite loop of main menu function until programmed is exit()-ed in
 * that function
 */
int main(void) {
  /*printf("\n\n\nAuto\n----------------------------\n\n");
  testComputeScoreAuto();
  printf("\n\n\nManual\n----------------------------\n\n");
  testComputeScoreManual();*/
  struct User* users[64];
  int m = 0;
  srand((unsigned int)time(0));
  while (1) runMainMenu(users, &m);

  return 0;
}
