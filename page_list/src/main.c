#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
  int codeNum;
  int viewCount;
  struct ListNode *next;
} ListNode;

typedef struct List {
  ListNode *head;
  ListNode *tail;
  int len;
  int n;
  int k;
} List;

static void firstLook(List *list, int codeNum) {
  ListNode *newNode = malloc(sizeof(ListNode));
  newNode->codeNum = codeNum;
  newNode->viewCount = 1;
  newNode->next = list->head;
  if (list->tail == 0) {
    list->tail = newNode;
  }
  list->head = newNode;
  ++list->len;
  if (list->len == list->n) {
    ListNode *cur = list->head;
    while (cur != 0 && cur->next != 0 && cur->next->next != 0) {
      cur = cur->next;
    }
    if (cur != 0 && cur->next != 0) {
      free(cur->next);
      cur->next = 0;
      --list->len;
    }
  }
}

static void nonFirstLook(ListNode *node, List *list) {
  ++node->viewCount;
  if (node->viewCount == list->k) {
    ListNode *cur = list->head;
    printf("cur: %p, node: %p\n", cur, node);
    if (cur != node) {
      while (cur->next != node) {
        cur = cur->next;
      }
      cur->next = cur->next->next;
      node->next = list->head;
      list->head = node;
    }
    node->viewCount = 0;
  }
}

static void lookAt(int codeNum, List *list) {
  ListNode *cur = list->head;
  int i;
  for (i = 0; i < list->len && cur->codeNum != codeNum && cur != 0; ++i) {
    cur = cur->next;
  }
  if (cur == 0) {
    firstLook(list, codeNum);
  } else {
    nonFirstLook(cur, list);
  }
}

static void printList(List *list) {
  ListNode *cur = list->head;
  while (cur) {
    printf("(%d, %d) ", cur->codeNum, cur->viewCount);
    cur = cur->next;
  }
}

int main(void) {
  List list;
  int n, k;
  printf("N, K: ");
  scanf("%d%d", &n, &k);
  list.n = n;
  list.k = k;
  list.len = 0;
  list.head = 0;
  list.tail = 0;
  lookAt(123, &list);
  lookAt(124, &list);
  lookAt(123, &list);
  lookAt(123, &list);
  lookAt(123, &list);
  printList(&list);
  printf("\n");
  ListNode *cur = list.head;
  while (cur != NULL) {
      ListNode *next = cur->next;
      free(cur);
      cur = next;
  }

  return 0;
}
