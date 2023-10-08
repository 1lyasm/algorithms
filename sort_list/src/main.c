#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

struct ListNode {
  int val;
  struct ListNode *next;
};

unsigned getLen(struct ListNode *head) {
  unsigned count = 0;
  struct ListNode *current = head;
  while (current) {
    ++count;
    current = current->next;
  }
  return count;
}

struct ListNode *sortList(struct ListNode *head) {
  unsigned isSorted = 0;
  for (unsigned width = 1; !isSorted; width *= 2) {
    struct ListNode *current = head;
    struct ListNode **nextPtr = &head;
    unsigned merge_count = 0;
    while (current) {
      struct ListNode *subLists[2];
      struct ListNode *subListTails[2] = {NULL, NULL};
      for (unsigned i = 0; i < 2; ++i) {
        subLists[i] = current;
        for (unsigned j = 0; j < width && current; ++j) {
          subListTails[i] = current;
          current = current->next;
        }
        if (subListTails[i]) {
          subListTails[i]->next = 0;
        }
      }
      while (subLists[0] && subLists[1]) {
        if (subLists[0]->val <= subLists[1]->val) {
          *nextPtr = subLists[0];
          nextPtr = &subLists[0]->next;
          subLists[0] = subLists[0]->next;
        } else {
          *nextPtr = subLists[1];
          nextPtr = &subLists[1]->next;
          subLists[1] = subLists[1]->next;
        }
      }
      if (subLists[0]) {
        *nextPtr = subLists[0];
        nextPtr = &subListTails[0]->next;
      } else {
        *nextPtr = subLists[1];
        nextPtr = &subListTails[1]->next;
      }
      ++merge_count;
    }
    if (merge_count <= 1) {
        isSorted = 1;
    }
  }
  return head;
}

void *emalloc(unsigned size) {
  void *result = malloc(size);
  if (!result) {
    fprintf(stderr, "%s: malloc failed", __func__);
    exit(EXIT_FAILURE);
  }
  return result;
}

struct ListNode *buildList(int *array, unsigned len) {
  struct ListNode *head = emalloc(sizeof(struct ListNode));
  head->val = array[0];
  struct ListNode *current = head;
  for (unsigned i = 1; i < len; ++i) {
    current->next = emalloc(sizeof(struct ListNode));
    current->next->val = array[i];
    current = current->next;
  }
  current->next = 0;
  return head;
}

void printList(struct ListNode *head) {
  printf("%s: ", __func__);
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

void freeList(struct ListNode *head) {
  struct ListNode *current = head;
  while (current) {
    struct ListNode *next = current->next;
    free(current);
    current = next;
  }
}

void testSortList() {
  int array[] = {7, 10, 6, 4, 5, 9, 1, 3, 2, 8};
  unsigned len = sizeof(array) / sizeof(array[0]);
  struct ListNode *head = buildList(array, len);
  printf("%s: before sort: ", __func__);
  printList(head);
  head = sortList(head);
  printf("%s: after sort: ", __func__);
  printList(head);
  freeList(head);
}

int main() { testSortList(); }
