#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void printArr(int *, int, int);
void assertArrEq(int *, int *, int);
void swap(int *, int, int);
int numIslands(char **, int, int *);
void numIslandsTest();
int *partitionLabels(char *, int *);
void partitionLabelsTest();
int twoSumSortCmp(const void *, const void *);
int twoSumSearchCmp(const void *, const void *);
int *twoSum(int *, int, int, int *);
void twoSumTest();
struct llist_node;
struct llist_node *addTwoNums(struct llist_node *, struct llist_node *);
void addTwoNumsTest();
void mergeSort(int *, int, int);
void mergeSortTest();
void merge(int *, int, int);
void quickSortTest();
void quickSort(int *, int, int);
struct Arr;
struct Arr *genArmstrong(int);
void genArmstrongTest();
int genNarcCmp(const void *, const void *);
int genNarcCmpRev(const void *, const void *);
int64_t *genNarc(int64_t);
void genNarcTest();
void ToHTest();
struct Sticks;
void ToH(struct Sticks *, int, int, int, int);
void putCircle(struct Sticks *, int, int);
void binarySearchTest();
int binarySearch(int *, int, int, int);
int binarySearchIter(int *, int, int);

int main() {
  printf("\n");
  binarySearchTest();
  printf("\n");
  return 0;
}

void printArr(int *Arr, int S, int E) {
  for (int I = S; I <= E; printf("%d ", Arr[I]), ++I)
    ;
  printf("\n");
}

void assertArrEq(int *Arr1, int *Arr2, int Len) {
  for (int I = 0; I < Len; assert(Arr1[I] == Arr2[I]), ++I)
    ;
}

void swap(int *Arr, int Idx1, int Idx2) {
  int T = Arr[Idx1];
  Arr[Idx1] = Arr[Idx2];
  Arr[Idx2] = T;
}

int numIslands(char **grid, int Size, int *ColSize) {
  int m = (*ColSize);
  int *idx_stack = malloc(2 * sizeof(int) * Size * m);
  int sp;
  int Cnt = 0;
  for (int i = 0; i < Size; i++) {
    for (int j = 0; j < m; j++) {
      int tmp = grid[i][j] - '0';
      Cnt += tmp;
      idx_stack[0] = i;
      idx_stack[1] = j;
      sp = 2 * tmp;
      for (; sp > 0;) {
        int x = idx_stack[sp - 2], y = idx_stack[sp - 1];
        grid[x][y] = '0';
        sp -= 2;
        idx_stack[sp] = x;
        idx_stack[sp + 1] = y + 1;
        sp += (2 * (((y + 1) < m) && (grid[x][y + 1] - '0')));
        idx_stack[sp] = x;
        idx_stack[sp + 1] = y - 1;
        sp += (2 * (((y - 1) >= 0) && (grid[x][y - 1] - '0')));
        idx_stack[sp] = x + 1;
        idx_stack[sp + 1] = y;
        sp += (2 * (((x + 1) < Size) && (grid[x + 1][y] - '0')));
        idx_stack[sp] = x - 1;
        idx_stack[sp + 1] = y;
        sp += (2 * (((x - 1) >= 0) && (grid[x - 1][y] - '0')));
      }
    }
  }
  free(idx_stack);
  idx_stack = 0;
  return Cnt;
}

void numIslandsTest() {
  char grid_[3][3] = {{'1', '1', '1'}, {'0', '1', '0'}, {'1', '1', '1'}};
  int Size = 3, ColSize = 3;
  char **grid = malloc(Size * sizeof(char *));
  for (int i = 0; i < Size; i++) {
    grid[i] = malloc(ColSize * sizeof(char));
    for (int j = 0; j < ColSize; j++) grid[i][j] = grid_[i][j];
  }
  int Cnt = numIslands(grid, Size, &ColSize);
  for (int i = 0; i < Size; i++) {
    free(grid[i]);
    grid[i] = 0;
  }
  free(grid);
  grid = 0;
}

int *partitionLabels(char *s, int *returnSize) {
  int last[26] = {0};
  int slen = strlen(s);
  for (int i = 0; i < slen; i++) last[s[i] - 'a'] = i;
  int *sizes = malloc(sizeof(int) * slen);
  int sp = 0;
  for (int i = 0, S = 0, furthest = -1; i < slen; i++) {
    furthest = fmax(last[s[i] - 'a'], furthest);
    if (i == furthest) {
      sizes[sp++] = i - S + 1;
      S = i + 1;
    }
  }
  (*returnSize) = sp;
  return sizes;
}

void partitionLabelsTest() {
  char *s = "ababcbacadefegdehijhklij";
  int returnSize;
  int *Res = partitionLabels(s, &returnSize);
  free(Res);
}

int twoSumSortCmp(const void *a, const void *b) {
  int L = *(int *)a, R = *(int *)b;
  if (L > R)
    return 1;
  else if (L < R)
    return -1;
  return 0;
}

int twoSumSearchCmp(const void *a, const void *b) {
  int key = *(int *)a, elem = *(int *)b;
  if (key < elem)
    return -1;
  else if (key > elem)
    return 1;
  return 0;
}

int *twoSum(int *nums, int Size, int target, int *returnSize) {
  int *arr = malloc(Size * sizeof(int));
  memcpy(arr, nums, Size * sizeof(int));
  qsort(arr, Size, sizeof(int), twoSumSortCmp);
  int *reduced_arr = malloc(Size * sizeof(int)), reduced_size = 1;
  reduced_arr[0] = arr[0];
  for (int i = 0; i < Size; i++) {
    int elem = arr[i];
    if (elem != reduced_arr[reduced_size - 1]) {
      reduced_arr[reduced_size] = elem;
      reduced_size++;
    }
  }
  free(arr);
  arr = 0;
  int *indices = 0;
  for (int i = 0; i < reduced_size; i++) {
    int key = target - reduced_arr[i];
    void *search_Res =
        bsearch(&key, reduced_arr, reduced_size, sizeof(int), twoSumSearchCmp);
    if (!search_Res) continue;
    indices = malloc(2 * sizeof(int));
    int val_0 = reduced_arr[i], val_1 = *(int *)search_Res;
    for (int i = Size - 1; i >= 0; i--) {
      if (nums[i] == val_0) indices[0] = i;
    }
    for (int i = 0; i < Size; i++) {
      if (nums[i] == val_1) indices[1] = i;
    }
    *returnSize = 2;
    break;
  }
  free(reduced_arr);
  reduced_arr = 0;
  return indices;
}

void twoSumTest() {
  int nums[4] = {2, 7, 11, 15}, Size = 4, target = 9, returnSize = 0;
  int *output = twoSum(nums, Size, target, &returnSize);
  free(output);
  output = 0;
}

struct llist_node {
  int val;
  struct llist_node *next;
};

struct llist_node *addTwoNums(struct llist_node *l1, struct llist_node *l2) {
  struct llist_node *head = malloc(sizeof(struct llist_node)), *cur = head;
  int sum = l1->val + l2->val, carry = sum / 10;
  cur->val = sum % 10;
  l1 = l1->next;
  l2 = l2->next;
  while (l1 || l2 || carry) {
    sum = carry;
    if (l1) {
      sum += l1->val;
      l1 = l1->next;
    }
    if (l2) {
      sum += l2->val;
      l2 = l2->next;
    }
    carry = sum / 10;
    cur = cur->next = malloc(sizeof(struct llist_node));
    cur->val = sum % 10;
  }
  cur->next = 0;
  return head;
}

void addTwoNumsTest() {
  int arr1[3] = {2, 4, 9}, len1 = 3, arr2[3] = {5, 6, 4}, len2 = 3;
  struct llist_node *l1 = malloc(sizeof(struct llist_node)),
                    *l2 = malloc(sizeof(struct llist_node));
  struct llist_node *a = l1, *b = l2;
  for (int i = 0; i < len1 - 1; i++) {
    a->val = arr1[i];
    a->next = malloc(sizeof(struct llist_node));
    a = a->next;
  }
  a->val = arr1[len1 - 1];
  a->next = 0;
  for (int i = 0; i < len2 - 1; i++) {
    b->val = arr2[i];
    b->next = malloc(sizeof(struct llist_node));
    b = b->next;
  }
  b->val = arr2[len2 - 1];
  b->next = 0;
  struct llist_node *res = addTwoNums(l1, l2);
  while (res) {
    struct llist_node *next = res->next;
    free(res);
    res = next;
  }
  while (l1) {
    struct llist_node *next = l1->next;
    free(l1);
    l1 = next;
  }
  while (l2) {
    struct llist_node *next = l2->next;
    free(l2);
    l2 = next;
  }
}

void mergeSort(int *Arr, int S, int E) {
  if (E - S <= 1) {
    merge(Arr, S, E);
    return;
  }
  int RS = (S + E + 1) / 2;
  mergeSort(Arr, S, RS - 1);
  mergeSort(Arr, RS, E);
  merge(Arr, S, E);
}

void merge(int *Arr, int S, int E) {
  if (E == S) return;
  int M = (E + S - 1) / 2;
  int *ExtraArr = malloc((E - S + 1) * sizeof(int));
  int I = E - S, L = M, R = E;
  for (; I >= 0 && L >= S && R >= M + 1; --I) {
    if (Arr[R] > Arr[L])
      ExtraArr[I] = Arr[R--];
    else
      ExtraArr[I] = Arr[L--];
  }
  int Longer, Stop;
  if (L >= S) {
    Longer = L;
    Stop = S;
  } else {
    Longer = R;
    Stop = M + 1;
  }
  for (; Longer >= Stop; --Longer, --I) ExtraArr[I] = Arr[Longer];
  for (int I = 0; I < E - S + 1; ++I) Arr[S + I] = ExtraArr[I];
  free(ExtraArr);
}

void mergeSortTest() {
  printf("\nmergeSortTest: ");
  {
    int Inp[6] = {1, 4, 9, 2, 3, 8}, Correct[6] = {1, 2, 3, 4, 8, 9};
    int Len = sizeof(Inp) / sizeof(Inp[0]);
    mergeSort(Inp, 0, Len - 1);
    assertArrEq(Inp, Correct, Len);
  }
  {
    int Inp[6] = {1, 2, 3, 4, 5, 6}, Correct[6] = {1, 2, 3, 4, 5, 6};
    int Len = sizeof(Inp) / sizeof(Inp[0]);
    mergeSort(Inp, 0, Len - 1);
    assertArrEq(Inp, Correct, Len);
  }
  {
    int Inp[5] = {1, 4, 9, 2, 3}, Correct[5] = {1, 2, 3, 4, 9};
    int Len = sizeof(Inp) / sizeof(Inp[0]);
    mergeSort(Inp, 0, Len - 1);
    assertArrEq(Inp, Correct, Len);
  }
  {
    int Inp[3] = {3, 2, 1}, Correct[3] = {1, 2, 3};
    int Len = sizeof(Inp) / sizeof(Inp[0]);
    mergeSort(Inp, 0, Len - 1);
    assertArrEq(Inp, Correct, Len);
  }
  {
    int Inp[3] = {3, 3, 3}, Correct[3] = {3, 3, 3};
    int Len = sizeof(Inp) / sizeof(Inp[0]);
    mergeSort(Inp, 0, Len - 1);
    assertArrEq(Inp, Correct, Len);
  }
  {
    int Inp[2] = {2, 1}, Correct[2] = {1, 2};
    int Len = sizeof(Inp) / sizeof(Inp[0]);
    mergeSort(Inp, 0, Len - 1);
    assertArrEq(Inp, Correct, Len);
  }
  {
    int Inp[1] = {1}, Correct[1] = {1};
    int Len = sizeof(Inp) / sizeof(Inp[0]);
    mergeSort(Inp, 0, Len - 1);
    assertArrEq(Inp, Correct, Len);
  }
  {
    int Inp[12] = {1, 3, 2, 4, 0, -12, 12, 23, -4, 35, -12, 43},
        Correct[12] = {-12, -12, -4, 0, 1, 2, 3, 4, 12, 23, 35, 43};
    int Len = sizeof(Inp) / sizeof(Inp[0]);
    mergeSort(Inp, 0, Len - 1);
    assertArrEq(Inp, Correct, Len);
  }
  {
    int Inp[6] = {6, 5, 4, 3, 2, 1}, Correct[6] = {1, 2, 3, 4, 5, 6};
    int Len = sizeof(Inp) / sizeof(Inp[0]);
    mergeSort(Inp, 0, Len - 1);
    assertArrEq(Inp, Correct, Len);
  }
  printf("PASSED\n");
}

void quickSort(int *Arr, int S, int E) {
  if (S >= E) return;
  int Pivot = S + rand() % (E - S + 1), PivotVal = Arr[Pivot];
  swap(Arr, Pivot, E);
  int NewPivot = -1;
  for (int L = S, R = E - 1;;) {
    for (; Arr[L] <= PivotVal && L <= E - 1; ++L)
      ;
    for (; Arr[R] >= PivotVal && R >= L + 1; --R)
      ;
    if (L >= E) {
      NewPivot = E;
      break;
    } else if (R <= L) {
      swap(Arr, L, E);
      NewPivot = L;
      break;
    }
    swap(Arr, L, R);
  }
  quickSort(Arr, S, NewPivot - 1);
  quickSort(Arr, NewPivot + 1, E);
}

void quickSortTest() {
  printf("\nquickSortTest: ");
  {
    int Inp[6] = {1, 4, 9, 2, 3, 8}, Correct[6] = {1, 2, 3, 4, 8, 9};
    int Len = sizeof(Inp) / sizeof(Inp[0]);
    quickSort(Inp, 0, Len - 1);
    assertArrEq(Inp, Correct, Len);
  }
  {
    int Inp[6] = {1, 2, 3, 4, 5, 6}, Correct[6] = {1, 2, 3, 4, 5, 6};
    int Len = sizeof(Inp) / sizeof(Inp[0]);
    quickSort(Inp, 0, Len - 1);
    assertArrEq(Inp, Correct, Len);
  }
  {
    int Inp[5] = {1, 4, 9, 2, 3}, Correct[5] = {1, 2, 3, 4, 9};
    int Len = sizeof(Inp) / sizeof(Inp[0]);
    quickSort(Inp, 0, Len - 1);
    assertArrEq(Inp, Correct, Len);
  }
  {
    int Inp[3] = {3, 2, 1}, Correct[3] = {1, 2, 3};
    int Len = sizeof(Inp) / sizeof(Inp[0]);
    quickSort(Inp, 0, Len - 1);
    assertArrEq(Inp, Correct, Len);
  }
  {
    int Inp[3] = {3, 3, 3}, Correct[3] = {3, 3, 3};
    int Len = sizeof(Inp) / sizeof(Inp[0]);
    quickSort(Inp, 0, Len - 1);
    assertArrEq(Inp, Correct, Len);
  }
  {
    int Inp[2] = {2, 1}, Correct[2] = {1, 2};
    int Len = sizeof(Inp) / sizeof(Inp[0]);
    quickSort(Inp, 0, Len - 1);
    assertArrEq(Inp, Correct, Len);
  }
  {
    int Inp[1] = {1}, Correct[1] = {1};
    int Len = sizeof(Inp) / sizeof(Inp[0]);
    quickSort(Inp, 0, Len - 1);
    assertArrEq(Inp, Correct, Len);
  }
  {
    int Inp[12] = {1, 3, 2, 4, 0, -12, 12, 23, -4, 35, -12, 43},
        Correct[12] = {-12, -12, -4, 0, 1, 2, 3, 4, 12, 23, 35, 43};
    int Len = sizeof(Inp) / sizeof(Inp[0]);
    quickSort(Inp, 0, Len - 1);
    assertArrEq(Inp, Correct, Len);
  }
  {
    int Inp[6] = {6, 5, 4, 3, 2, 1}, Correct[6] = {1, 2, 3, 4, 5, 6};
    int Len = sizeof(Inp) / sizeof(Inp[0]);
    quickSort(Inp, 0, Len - 1);
    assertArrEq(Inp, Correct, Len);
  }
  printf("PASSED\n");
}

struct Arr {
  int Len;
  int64_t *ArrPtr;
};

struct Arr *genArmstrong(int N) {
  int ResLen = 0;
  struct Arr *Res = malloc(sizeof(struct Arr *));
  Res->ArrPtr = malloc(N * sizeof(int));
  for (int Num = 0; Num < N; ++Num) {
    int Sum = 0, MutatedNum = Num, Last = Num % 10;
    Sum += Last * Last * Last;
    MutatedNum /= 10;
    Last = MutatedNum % 10;
    Sum += Last * Last * Last;
    MutatedNum /= 10;
    Last = MutatedNum % 10;
    Sum += Last * Last * Last;
    if (Sum == Num) Res->ArrPtr[ResLen++] = Num;
  }
  Res->Len = ResLen;
  return Res;
}

void genArmstrongTest() {
  printf("\ngenArmstrongTest: ");
  struct Arr *Res = genArmstrong(1000);
  int Correct[] = {0, 1, 153, 370, 371, 407};
  int CorrectLen = sizeof(Correct) / sizeof(Correct[0]);
  assert(Res->Len == CorrectLen);
  for (int I = 0; I < Res->Len; ++I) assert(Res->ArrPtr[I] == Correct[I]);
  free(Res->ArrPtr);
  Res->ArrPtr = 0;
  free(Res);
  Res = 0;
  printf("PASSED\n");
}

int64_t *genNarc(int64_t N) {
  int DigitCnt = ceil(log10(N)) + 1;
  int64_t *Res = malloc(100 * sizeof(int64_t));
  for (int I = 1; I <= 9; Res[I] = I, ++I)
    ;
  int ResLen = 10, RowCnt = 10, ColCnt = DigitCnt - 1;
  int64_t **Powers = malloc(RowCnt * sizeof(int64_t *));
  for (int I = 0; I < RowCnt; ++I) {
    Powers[I] = malloc(ColCnt * sizeof(int64_t));
    for (int J = 0; J < ColCnt; Powers[I][J] = pow(I, J + 1), ++J)
      ;
  }
  for (int NumLen = 2; NumLen < DigitCnt; ++NumLen) {
    int *Num = calloc(NumLen, sizeof(int));
    for (int64_t Sum = 0;;) {
      for (int I = 0; I < NumLen; Sum += Powers[Num[I]][NumLen - 1], ++I)
        ;
      int64_t SumCopy = Sum;
      int *SumArr = malloc(NumLen * sizeof(int)), SumLen = 0;
      for (; Sum > 0 && SumLen < NumLen; SumArr[SumLen++] = Sum % 10, Sum /= 10)
        ;
      if (Sum == 0 && SumLen == NumLen) {
        qsort(SumArr, NumLen, sizeof(int), genNarcCmp);
        if (memcmp((const void *)SumArr, (const void *)Num,
                   NumLen * sizeof(int)) == 0)
          Res[ResLen++] = SumCopy;
      }
      free(SumArr);
      SumArr = 0;
      if (++Num[0] == 10) {
        int J = 1;
        for (; J < NumLen && Num[J] == 9; ++J)
          ;
        if (J == NumLen) {
          break;
        }
        for (int K = J - 1, Val = ++Num[J]; K >= 0; Num[K] = Val, --K)
          ;
      }
    }
    free(Num);
    Num = 0;
  }
  for (int I = 0; I < RowCnt; free(Powers[I]), ++I, Powers[I] = 0)
    ;
  free(Powers);
  Powers = 0;
  for (int I = 0; I < ResLen - 1; Res[I] = Res[I + 1], ++I)
    ;
  qsort(Res, ResLen - 1, sizeof(int64_t), genNarcCmpRev);
  for (int I = ResLen; I >= 1; Res[I] = Res[I - 1], --I)
    ;
  Res[0] = ResLen;
  return Res;
}

int genNarcCmp(const void *a, const void *b) {
  int arg1 = *(const int *)a;
  int arg2 = *(const int *)b;
  if (arg1 < arg2) return 1;
  if (arg1 > arg2) return -1;
  return 0;
}

int genNarcCmpRev(const void *a, const void *b) {
  int64_t arg1 = *(const int64_t *)a;
  int64_t arg2 = *(const int64_t *)b;
  if (arg1 < arg2) return -1;
  if (arg1 > arg2) return 1;
  return 0;
}

void genNarcTest() {
  printf("\ngenNarcTest: ");
  int64_t *Res = genNarc(100000000000);
  int64_t Correct[] = {
      1,           2,           3,           4,           5,
      6,           7,           8,           9,           153,
      370,         371,         407,         1634,        8208,
      9474,        54748,       92727,       93084,       548834,
      1741725,     4210818,     9800817,     9926315,     24678050,
      24678051,    88593477,    146511208,   472335975,   534494836,
      912985153,   4679307774,  32164049650, 32164049651, 40028394225,
      42678290603, 44708635679, 49388550606, 82693916578, 94204591914};
  int64_t CorrectLen = sizeof(Correct) / sizeof(Correct[0]);
  assert(Res[0] - 1 == CorrectLen);
  for (int I = 1; I < Res[0]; ++I) assert(Res[I] == Correct[I - 1]);
  free(Res);
  Res = 0;
  printf("PASSED\n");
}

struct Sticks {
  int **StickMatrix;
  int Tops[3];
};

void ToHTest() {
  printf("\nToHTest: ");
  int N = 30;
  struct Sticks *Towers = malloc(sizeof(struct Sticks));
  Towers->StickMatrix = malloc(3 * sizeof(int *));
  for (int I = 0; I < 3; ++I) {
    Towers->StickMatrix[I] = malloc(N * sizeof(int));
    memset((void *)Towers->StickMatrix[I], -1, N * sizeof(int));
  }
  for (int J = 0; J < N; ++J) {
    Towers->StickMatrix[0][J] = N - J;
  }
  Towers->Tops[0] = N;
  Towers->Tops[1] = 0;
  Towers->Tops[2] = 0;
  int *Expected1 = malloc(N * sizeof(int));
  int *Expected2 = malloc(N * sizeof(int));
  int *Expected3 = malloc(N * sizeof(int));
  memset(Expected1, -1, N * sizeof(int));
  for (int J = 0; J < N; ++J) {
    Expected2[J] = N - J;
  }
  memset(Expected3, -1, N * sizeof(int));
  ToH(Towers, 0, 1, N, N);
  assertArrEq(Towers->StickMatrix[0], Expected1, N);
  assertArrEq(Towers->StickMatrix[1], Expected2, N);
  assertArrEq(Towers->StickMatrix[2], Expected3, N);
  for (int I = 0; I < 3; ++I) {
    free(Towers->StickMatrix[I]);
  }
  free(Towers->StickMatrix);
  free(Towers);
  printf("PASSED\n");
}

void ToH(struct Sticks *Towers, int Source, int Destination, int Count, int N) {
  assert(Source <= 2);
  assert(Source >= 0);
  assert(Destination <= 2);
  assert(Destination >= 0);
  assert(Source != Destination);
  int OtherDestination = 0;
  if (OtherDestination == Source || OtherDestination == Destination) {
    OtherDestination++;
  }
  if (OtherDestination == Source || OtherDestination == Destination) {
    OtherDestination++;
  }
  if (Count == 2) {
    if (abs(Destination - Source) == 1) {
      putCircle(Towers, Source, OtherDestination);
      putCircle(Towers, Source, Destination);
      putCircle(Towers, OtherDestination, Destination);
    }
    if (abs(Destination - Source) == 2) {
      putCircle(Towers, Source, OtherDestination);
      putCircle(Towers, Source, Destination);
      putCircle(Towers, OtherDestination, Destination);
    }
    return;
  }
  ToH(Towers, Source, OtherDestination, Count - 1, N);
  putCircle(Towers, Source, Destination);
  ToH(Towers, OtherDestination, Destination, Count - 1, N);
}

void putCircle(struct Sticks *Towers, int Source, int Destination) {
  int SourceTop = Towers->Tops[Source];
  int DestinationTop = Towers->Tops[Destination];
  Towers->StickMatrix[Destination][DestinationTop++] =
      Towers->StickMatrix[Source][SourceTop - 1];
  Towers->StickMatrix[Source][SourceTop-- - 1] = -1;
  Towers->Tops[Source]--;
  Towers->Tops[Destination]++;
}

void binarySearchTest() {
  printf("\nbinarySearchTest: ");
  int Arr[5] = {2, 2, 3, 3, 5};
  int N = sizeof(Arr) / sizeof(int);
  assert(binarySearch(Arr, 0, N - 1, 1) == -1);
  assert(binarySearch(Arr, 0, N - 1, 2) == 0);
  assert(binarySearch(Arr, 0, N - 1, 3) == 2);
  assert(binarySearch(Arr, 0, N - 1, 4) == -1);
  assert(binarySearch(Arr, 0, N - 1, 5) == 4);
  assert(binarySearch(Arr, 0, N - 1, 6) == -1);

  assert(binarySearchIter(Arr, N, 1) == -1);
  assert(binarySearchIter(Arr, N, 2) == 0);
  assert(binarySearchIter(Arr, N, 3) == 2);
  assert(binarySearchIter(Arr, N, 4) == -1);
  assert(binarySearchIter(Arr, N, 5) == 4);
  assert(binarySearchIter(Arr, N, 6) == -1);
  printf("PASSED\n");
}

int binarySearch(int *Arr, int Start, int End, int Target) {
  if (Start > End) {
    return -1;
  }
  int Middle = (Start + End) / 2;
  if (Arr[Middle] == Target) {
    return Middle;
  } else if (Arr[Middle] < Target) {
    return binarySearch(Arr, Middle + 1, End, Target);
  } else {
    return binarySearch(Arr, 0, Middle - 1, Target);
  }
}

int binarySearchIter(int *Arr, int N, int Target) {
  int Start = 0;
  int End = N - 1;
  for (; Start <= End;) {
    int Middle = (Start + End) / 2;
    if (Arr[Middle] == Target) {
      return Middle;
    } else if (Arr[Middle] < Target) {
      Start = Middle + 1;
    } else {
      End = Middle - 1;
    }
  }
  return -1;
}
