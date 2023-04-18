#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
  int *arr;
  int top;
} Stack;

typedef struct TreeNode {
  int originalVal;
  int currentVal;
  int height;
  struct TreeNode *left;
  struct TreeNode *right;
  struct TreeNode *parent;
} TreeNode;

typedef struct ListNode {
  int val;
  struct ListNode *next;
} ListNode;

typedef struct List {
  ListNode *head;
  ListNode *tail;
  int len;
} List;

typedef struct ListNodeTreeNodePtr {
  TreeNode *val;
  struct ListNodeTreeNodePtr *next;
} ListNodeTreeNodePtr;

typedef struct ListTreeNodePtr {
  ListNodeTreeNodePtr *head;
  ListNodeTreeNodePtr *tail;
  int len;
} ListTreeNodePtr;

static void printList(List *list) {
  ListNode *it = list->head;
  do {
    printf("%d   ", it->val);
    it = it->next;
  } while (it != list->head);
  printf("\n");
}

static void pushFirstNodeList(List *list, int val) {
  list->head = malloc(sizeof(ListNode));
  list->head->val = val;
  list->head->next = list->head;
  list->tail = list->head;
  ++list->len;
}

static void pushFirstNodeListTreeNodePtr(ListTreeNodePtr *list, TreeNode *val) {
  list->head = calloc(1, sizeof(ListNodeTreeNodePtr));
  list->head->val = val;
  list->head->next = list->head;
  list->tail = list->head;
  ++list->len;
}

static void pushBackList(List *list, int val) {
  if (list->head == 0) {
    pushFirstNodeList(list, val);
    return;
  }
  list->tail->next = malloc(sizeof(struct ListNode));
  list->tail = list->tail->next;
  list->tail->val = val;
  list->tail->next = list->head;
  ++list->len;
}

static void pushBackListTreeNodePtr(ListTreeNodePtr *list, TreeNode *val) {
  if (list->head == 0) {
    pushFirstNodeListTreeNodePtr(list, val);
    return;
  }
  list->tail->next = calloc(1, sizeof(struct ListNodeTreeNodePtr));
  list->tail = list->tail->next;
  list->tail->val = val;
  list->tail->next = list->head;
  ++list->len;
}

static void popFrontListTreeNodePtr(ListTreeNodePtr *list) {
  ListNodeTreeNodePtr *oldNext;
  if (list->head == 0) {
    return;
  }
  if (list->head == list->tail) {
    free(list->head);
    list->head = 0;
    list->tail = 0;
    return;
  }
  oldNext = list->head->next;
  free(list->head);
  list->head = oldNext;
  --list->len;
}

static void delList(List *list) {
  ListNode *head_copy = list->head, *it = list->head, *next_it;
  do {
    next_it = it->next;
    free(it);
    it = 0;
    it = next_it;
  } while (it != head_copy);
}

static void insertAtIterList(List *list, ListNode *it, int val) {
  ListNode *old_next = it->next;
  it->next = malloc(sizeof(ListNode));
  it->next->val = val;
  it->next->next = old_next;
  ++list->len;
}

static void pushFrontList(List *list, int val) {
  ListNode *new_head = malloc(sizeof(ListNode));
  new_head->val = val;
  new_head->next = list->head;
  list->head = new_head;
  list->tail->next = list->head;
  ++list->len;
}

static void insertAtIndList(List *list, int idx, int val) {
  ListNode *it = list->head;
  int i;
  if (idx == 0) {
    pushFrontList(list, val);
    return;
  }
  if (idx == 1) {
    insertAtIterList(list, it, val);
    return;
  }
  it = it->next;
  for (i = 1; it != list->head && i < idx - 1; ++i) {
    it = it->next;
  }
  if (it == list->head) {
    pushBackList(list, val);
    return;
  }
  insertAtIterList(list, it, val);
}

static int convertInput(long *n, long *m, char *buf) {
  char *end;
  errno = 0;
  *n = strtol(buf, &end, 10);
  *m = strtol(end, &end, 10);
  if (*n == 0 || *m == 0 || errno == ERANGE) {
    return 1;
  } else {
    return 0;
  }
}

static int verifyInput(long n, long m) {
  if (n < 2 || m < 2) {
    return 1;
  } else {
    return 0;
  }
}

static void takeInp(long *val_1, long *val_2, char *prompt) {
  char buf[1024];
  printf("%s", prompt);
  do {
    fgets(buf, sizeof(buf), stdin);
  } while (buf[0] == '\n');
  if (convertInput(val_1, val_2, buf) == 1) {
    printf("Invalid input, try again\n");
    takeInp(val_1, val_2, prompt);
  }
  // if (verifyInput(*val_1, *val_2) == 1) {
  //   printf("Invalid input, try again\n");
  //   takeInp(val_1, val_2, prompt);
  // }
}

static void generateSortedList(List *list, int maxVal, int nodeCount) {
  int i;
  pushFirstNodeList(list, rand() % maxVal + 1);
  for (i = 1; i < nodeCount; ++i) {
    int randVal = rand() % maxVal + 1;
    ListNode *it = list->head;
    int j = 0;
    while (1) {
      if (randVal < it->val) {
        break;
      }
      ++j;
      it = it->next;
      if (it == list->head) {
        break;
      }
    }
    insertAtIndList(list, j, randVal);
  }
}

typedef struct StackTreeNodePtr {
  TreeNode **arr;
  int top;
} StackTreeNodePtr;

static int isEmptyStackTreeNodePtr(StackTreeNodePtr *st) {
  if (st->top <= 0) {
    return 1;
  } else {
    return 0;
  }
}

static void pushBackStackTreeNodePtr(StackTreeNodePtr *st, TreeNode *item) {
  st->arr[st->top++] = item;
}

static void popBackStackTreeNodePtr(StackTreeNodePtr *st) { --st->top; }

static int getHeight(TreeNode *root) {
  if (root == 0) {
    return -1;
  } else {
    return root->height;
  }
}

static TreeNode *sortedListToBST(List *list) {
  TreeNode *root;
  int counter, nodeCount;
  ListTreeNodePtr parents;
  StackTreeNodePtr stack;
  ListNode *listIt;
  TreeNode *treeIt;
  if (list->head == 0 || list == 0) {
    return 0;
  }
  root = calloc(1, sizeof(TreeNode));
  root->parent = 0;
  counter = 1;
  memset(&parents, 0, sizeof(ListTreeNodePtr));
  pushFirstNodeListTreeNodePtr(&parents, root);
  nodeCount = list->len;
  while (counter < nodeCount) {
    parents.head->val->left = calloc(1, sizeof(TreeNode));
    parents.head->val->left->height = 0;
    parents.head->val->left->parent = parents.head->val;
    pushBackListTreeNodePtr(&parents, parents.head->val->left);
    ++counter;
    if (counter >= nodeCount) {
      break;
    }
    parents.head->val->right = calloc(1, sizeof(TreeNode));
    parents.head->val->right->height = 0;
    parents.head->val->right->parent = parents.head->val;
    pushBackListTreeNodePtr(&parents, parents.head->val->right);
    ++counter;
    if (counter >= nodeCount) {
      break;
    }
    popFrontListTreeNodePtr(&parents);
  }
  stack.top = 0;
  stack.arr = calloc(256, sizeof(TreeNode *));
  listIt = list->head;
  treeIt = root;
  while (treeIt != 0 || !isEmptyStackTreeNodePtr(&stack)) {
    while (treeIt != 0) {
      pushBackStackTreeNodePtr(&stack, treeIt);
      treeIt = treeIt->left;
    }
    stack.arr[stack.top - 1]->originalVal = listIt->val;
    stack.arr[stack.top - 1]->currentVal = listIt->val;
    if (getHeight(stack.arr[stack.top - 1]->left) >
        getHeight(stack.arr[stack.top - 1]->right)) {
      stack.arr[stack.top - 1]->height =
          getHeight(stack.arr[stack.top - 1]->left) + 1;
    } else {
      stack.arr[stack.top - 1]->height =
          getHeight(stack.arr[stack.top - 1]->right) + 1;
    }
    listIt = listIt->next;
    treeIt = stack.arr[stack.top - 1];
    popBackStackTreeNodePtr(&stack);
    treeIt = treeIt->right;
  }
  free(stack.arr);
  return root;
}

static void printTree(TreeNode *root) {
  if (root == 0) {
    return;
  }
  printTree(root->left);
  printf("(%d, %d, %d) ", root->originalVal, root->currentVal, root->height);
  printTree(root->right);
}

static TreeNode *generateBST(int maxVal, int nodeCount) {
  List list = {0};
  TreeNode *root;
  generateSortedList(&list, maxVal, nodeCount);
  root = sortedListToBST(&list);
  delList(&list);
  return root;
}

static void freeTree(TreeNode *root) {
  TreeNode *rs;
  if (root == 0) {
    return;
  }
  freeTree(root->left);
  rs = root->right;
  free(root);
  freeTree(rs);
}

static TreeNode *deleteNode(TreeNode *root, int key) {
  if (root == 0) {
    return 0;
  }
  if (key < root->originalVal) {
    root->left = deleteNode(root->left, key);
  } else if (key > root->originalVal) {
    root->right = deleteNode(root->right, key);
  } else {
    if (root->left == 0) {
      return root->right;
    } else if (root->right == 0) {
      return root->left;
    }
    struct TreeNode *cur = root->right;
    while (cur->left != 0) {
      cur = cur->left;
    }
    root->originalVal = cur->originalVal;
    root->currentVal = cur->currentVal;
    root->right = deleteNode(root->right, root->originalVal);
  }
  return root;
}

static void printStack(Stack *st) {
  int i = 0;
  printf("\n\nbucket: ");
  for (i = 0; i < st->top; ++i) {
    printf("%d ", st->arr[i]);
  }
}

static void pushBackStack(Stack *st, int item) { st->arr[st->top++] = item; }

static int damage(TreeNode *root, long val, long power, Stack *bucket) {
  TreeNode *cur = root;
  TreeNode *parentIt;
  while (1) {
    if (val < cur->originalVal) {
      cur = cur->left;
    } else if (val > cur->originalVal) {
      cur = cur->right;
    } else {
      break;
    }
    if (cur == 0) {
      return 1;
    }
  }
  cur->currentVal -= power;
  if (cur->currentVal <= 0) {
    pushBackStack(bucket, cur->originalVal);
    if (cur->parent == 0) {
      if (cur->left != 0) {
        cur->parent = cur->left;
        cur->left = 0;
        cur->parent->right = deleteNode(cur, val);
        return 0;
      } else if (cur->right != 0) {
        cur->parent = cur->right;
        cur->right = 0;
        cur->parent->left = deleteNode(cur, val);
        return 0;
      }
    } else if (cur == cur->parent->left) {
      cur->parent->left = deleteNode(cur, val);
      return 0;
    } else {
      cur->parent->right = deleteNode(cur, val);
      return 0;
    }
  }
  return 0;
}

static void play(TreeNode *root) {
  long k, p;
  Stack bucket;
  int attackResult;
  bucket.top = 0;
  bucket.arr = calloc(1024, sizeof(int));
  while (root != 0) {
    printTree(root);
    printStack(&bucket);
    takeInp(&k, &p, "\n\nvalue of fruit (k) and attack power (p): ");
    attackResult = damage(root, k, p, &bucket);
    if (attackResult == 1) {
      printf("\nfruit with that value not found, try another one\n\n");
    }
  }
}

static void foodGame(void) {
  long n, m;
  TreeNode *root;
  takeInp(&n, &m, "N and M: ");
  root = generateBST(n, m);
  play(root);
  freeTree(root);
}

int main(void) {
  srand((unsigned int)time((time_t *)0));
  foodGame();
  return 0;
}
