#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct ListNode {
  int val;
  struct ListNode *next;
};

static unsigned getLen(struct ListNode *head) {
  unsigned len = 0;
  struct ListNode *current = head;
  while (current) {
    current = current->next;
    ++len;
  }
  return len;
}

static struct ListNode *get(struct ListNode *head, unsigned index) {
  printf("%s: index = %d\n\n", __func__, index);
  struct ListNode *current = head;
  for (unsigned i = 0; i < index; ++i) {
    current = current->next;
  }
  return current;
}

void printList(struct ListNode *head) {
  struct ListNode *current = head;
  while (current) {
    printf("%d", current->val);
    if (current->next) {
      printf(", ");
    }
    current = current->next;
  }
  printf("\n");
}

static struct ListNode *merge(struct ListNode *left, struct ListNode *right,
                              struct ListNode **last, unsigned width) {
  struct ListNode *cur_left = left, *cur_right = right, *initial_left = 0,
                  *initial_right = 0, *right_next = 0, *last_left = left;
  struct ListNode *newHead = left;
  struct ListNode *nextNode = right;
  printf("merge called\n\n");
  printf("width: %u\n\n", width);
  if (width != 1) {
    for (unsigned i = 0; i < width / 2 + 1; ++i) {
      nextNode = nextNode->next;
    }
  } else {
    nextNode = nextNode->next;
  }
  if (nextNode) {
    printf("%s: nextNode = %d\n\n", __func__, nextNode->val);
  } else {
    printf("%s: nextNode = null\n\n", __func__);
  }
  if (left->next == right && left->val > right->val) {
    printf("neighbor\n\n");
    right->next = left;
    left->next = nextNode;
    newHead = right;
    *last = left;
    printf("%s: newHead = %d\n\n", __func__, newHead->val);
    return newHead;
  }
  unsigned right_ends = 0;
  printf("cur_left = %d, cur_left->next = %d, cur_right = %d\n\n",
         cur_left->val, cur_left->next->val, cur_right->val);
  while (cur_left != right && !right_ends && cur_right != nextNode) {
    printf("cur_left: %d\n\n", cur_left->val);
    printf("cur_right: %d\n\n", cur_right->val);
    if (cur_left->val <= cur_right->val) {
      printf("entering less than branch\n\n");
      /* printf("cur_left->val = %d, cur_right->val = %d\n\n", cur_left->val, */
      /* cur_right->val); */
      initial_left = cur_left;
      while (cur_left != right && cur_left->val <= cur_right->val) {
        last_left = cur_left;
        cur_left = cur_left->next;
        /* if (cur_left->next) { */
        /*   printf("cur_left->next = %d\n\n", cur_left->next->val); */
        /* } else { */
        /*   printf("cur_left->next = null\n\n"); */
        /* } */
        /* printf("cur_left = %d\n\n", cur_left->val); */
      }
      if (cur_left != right) {
        initial_right = cur_right;
        while (cur_right->next != nextNode &&
               cur_right->next->val <= cur_left->val) {
          cur_right = cur_right->next;
        }
        printf("less than branch: cur_right: %d\n\n", cur_right->val);
        printf("less than branch: cur_right->next: %d\n\n",
               cur_right->next->val);
        printf("less than branch: initial_left: %d\n\n", initial_left->val);
        printf("less than branch: initial_left->next: %d\n\n",
               initial_left->next->val);
        printf("less than branch: initial_right: %d\n\n", initial_right->val);
        printf("less than branch: cur_left: %d\n\n", cur_left->val);
        initial_left->next = initial_right;
        right_next = cur_right->next;
        cur_right->next = cur_left;
        if (right_next != nextNode) {
          cur_right = right_next;
        }
        printf("less than branh: new cur_right: %d\n\n", cur_right->val);
      }
    } else {
      printf("entering more than branch\n\n");
      if (cur_left->next == right) {
        cur_left->next = nextNode;
        right_ends = 1;
      } else {
        initial_right = cur_right;
        printf("initial_right: %d\n\n", initial_right->val);
        if (initial_right->next) {
          printf("initial_right->next: %d\n\n", initial_right->next->val);
        }
        printf("cur_right: %d\n\n", cur_right->val);
        printf("cur_right->next: %d\n\n", cur_right->next->val);
        printf("cur_right->next->next: %d\n\n", cur_right->next->next->val);
        while (cur_right->next != nextNode &&
               cur_right->next->val <= cur_left->val) {
          cur_right = cur_right->next;
          /* printf("hey\n\n"); */
        }
        /* printf("cur_right: %d, cur_right->next: %d\n\n", cur_right->val, */
        /* cur_right->next->val); */
        struct ListNode *rightNext = cur_right->next;
        if (rightNext == nextNode) {
          right_ends = 1;
        }
        cur_right->next = cur_left;
        newHead = initial_right;
        if (rightNext != nextNode) {
          cur_right = rightNext;
        }
        /* printf("cur_right = %d\n\n", cur_right->val); */
      }
    }
    if (last_left) {
      printf("last_left: %d\n\n", last_left->val);
    } else {
      printf("last_left: null\n\n");
    }
    if (cur_right) {
      printf("cur_right: %d\n\n", cur_right->val);
    } else {
      printf("cur_right: null\n\n");
    }
    if (left->val <= right->val) {
      if (last_left->val <= cur_right->val) {
        last_left->next = cur_right;
      } else {
        last_left->next = nextNode;
      }
    } else {
      cur_left = left;
      while (cur_left != right) {
        last_left = cur_left;
        cur_left = cur_left->next;
      }
      last_left->next = nextNode;
    }
    *last = cur_right;
    /* printf("exiting merge\n\n"); */
  }
    return newHead;
}

static struct ListNode *sortList(struct ListNode *head) {
  unsigned len = getLen(head);
  struct ListNode *newHead = head, *mergeHead;
  for (unsigned width = 1; width < len; width *= 2) {
    struct ListNode *last = 0;
    for (unsigned i = 0; i + width < len; i += 2 * width) {
      printf("index 1 = %u, index 2 = %u\n\n", i, i + width);
      struct ListNode *old_last = last;
      mergeHead = merge(get(newHead, i), get(newHead, i + width), &last, width);
      if (old_last) {
        old_last->next = mergeHead;
      }
      if (i == 0) {
        newHead = mergeHead;
      }

      printf("len: %u\n\n", getLen(newHead));
      printList(newHead);
    }
  }
  return newHead;
}

struct ListNode *buildList(int *array, unsigned arrayLen) {
  struct ListNode *head = malloc(sizeof(struct ListNode));
  struct ListNode *current;
  if (!head) {
    printf("%s: malloc failed\n", __func__);
    exit(EXIT_FAILURE);
  }
  head->val = array[0];
  current = head;
  for (unsigned i = 1; i < arrayLen; ++i) {
    current->next = malloc(sizeof(struct ListNode));
    if (!head) {
      printf("%s: malloc failed\n", __func__);
      exit(EXIT_FAILURE);
    }
    current->next->val = array[i];
    current = current->next;
  }
  current->next = 0;
  return head;
}

void freeList(struct ListNode *head) {
  struct ListNode *current = head;
  while (current) {
    struct ListNode *next = current->next;
    free(current);
    current = next;
  }
}

void testMerge() {
  {
    int array[] = {3, 10, 11, 12, 4, 5, 6, 19};
    unsigned arrayLen = sizeof(array) / sizeof(arrayLen);
    struct ListNode *head = buildList(array, arrayLen);
    struct ListNode *last;
    printList(head);
    head = merge(get(head, 0), get(head, 4), &last, 4);
    printList(head);
    freeList(head);
  }
  {
    int array[] = {7, 8, 1, 2};
    unsigned arrayLen = sizeof(array) / sizeof(arrayLen);
    struct ListNode *head = buildList(array, arrayLen);
    struct ListNode *last;
    printList(head);
    head = merge(get(head, 0), get(head, 2), &last, 2);
    printList(head);
    freeList(head);
  }
}

void testSortList() {
  /* { */
  /*   int array[] = {4, 2, 1, 3}; */
  /*   unsigned arrayLen = sizeof(array) / sizeof(arrayLen); */
  /*   struct ListNode *head = buildList(array, arrayLen); */
  /*   printList(head); */
  /*   head = sortList(head); */
  /*   printList(head); */
  /*   freeList(head); */
  /* } */
  {
    int array[] = {-1, 5, 3, 4, 0};
    unsigned arrayLen = sizeof(array) / sizeof(arrayLen);
    struct ListNode *head = buildList(array, arrayLen);
    printList(head);
    head = sortList(head);
    printList(head);
    freeList(head);
  }
}

int main() {
  /* testMerge(); */
  testSortList();
}
