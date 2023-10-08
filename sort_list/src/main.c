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

static struct ListNode *merge(struct ListNode *left,
                  struct ListNode *right) {
  struct ListNode *cur_left = left, *cur_right = right, *initial_left = 0,
                  *initial_right = 0, *right_next = 0, *last_left = left;
  struct ListNode *newHead = left;
  if (left->next == right) {
      printf("neighbor\n\n");
      right->next = left;
      left->next = 0;
      newHead = right;
      return newHead;
  }
  unsigned right_ends = 0;
  /* printf("cur_left = %d, cur_left->next = %d, cur_right = %d\n\n", */
         /* cur_left->val, cur_left->next->val, cur_right->val); */
  while (cur_left != right && !right_ends) {
    if (cur_left->val <= cur_right->val) {
      /* printf("cur_left->val = %d, cur_right->val = %d\n\n", cur_left->val, */
             /* cur_right->val); */
      initial_left = cur_left;
      while (cur_left != right && cur_left->val <= cur_right->val) {
        last_left = cur_left;
        cur_left = cur_left->next;
        /* printf("cur_left->next = %d\n\n", cur_left->next->val); */
        /* printf("cur_left = %d\n\n", cur_left->val); */
        /* printf("hey\n\n"); */
      }
      if (cur_left != right) {
        initial_right = cur_right;
        while (cur_right->next && cur_right->next->val <= cur_left->val) {
          cur_right = cur_right->next;
        }
        initial_left->next = initial_right;
        right_next = cur_right->next;
        cur_right->next = cur_left;
        cur_right = right_next;
      }
    } else {
      /* printf("hey\n\n"); */
      initial_right = cur_right;
      while (cur_right->next && cur_right->next->val <= cur_left->val) {
        cur_right = cur_right->next;
      }
      if (!cur_right->next) {
        right_ends = 1;
      }
      cur_right->next = cur_left;
      newHead = initial_right;
      /* printf("cur_right = %d\n\n", cur_right->val); */
    }
  }
  if (left->val <= right->val) {
    if (last_left->val <= cur_right->val) {
      last_left->next = cur_right;
    } else {
      last_left->next = 0;
    }
  } else {
    cur_left = left;
    while (cur_left != right) {
      last_left = cur_left;
      cur_left = cur_left->next;
    }
    last_left->next = 0;
  }
  /* printf("exiting merge\n\n"); */
  return newHead;
}

static struct ListNode *sortList(struct ListNode *head) {
  unsigned len = getLen(head);
  struct ListNode *newHead = head, *mergeHead;
  for (unsigned width = 1; width < len; width *= 2) {
    for (unsigned i = 0; i + width < len; i += 2 * width) {
      printf("index 1 = %u, index 2 = %u\n\n", i, i + width);

     mergeHead = merge(get(head, i), get(head, i + width));
      if (i == 0) {
          newHead = mergeHead;
      }

        printf("len: %u\n\n", getLen(head));
      printList(head);
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
    printList(head);
    head = merge(get(head, 0), get(head, 4));
    printList(head);
    freeList(head);
  }
  {
    int array[] = {7, 8, 1, 2};
    unsigned arrayLen = sizeof(array) / sizeof(arrayLen);
    struct ListNode *head = buildList(array, arrayLen);
    printList(head);
    head = merge(get(head, 0), get(head, 2));
    printList(head);
    freeList(head);
  }
}

void testSortList() {
  {
    int array[] = {4, 2, 1, 3};
    unsigned arrayLen = sizeof(array) / sizeof(arrayLen);
    struct ListNode *head = buildList(array, arrayLen);
    printList(head);
    head = sortList(head);
    printList(head);
    freeList(head);
  }
}

int main() {
  testSortList();
  /* testMerge(); */
}
