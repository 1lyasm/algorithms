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
  struct ListNode *current = head;
  for (unsigned i = 0; i < index; ++i) {
    current = current->next;
  }
  return current;
}

static void merge(struct ListNode *left, struct ListNode *right) {
    printf("left = %p, right = %p\n\n",
            (void *) left,
            (void *) right);

    if (!left || !right) {
        return;
    }

    if (left->next == right && left->val > right->val) {
        printf("neighbor\n\n");
        int left_val = left->val;
        left->val = right->val;
        right->val = left_val;
        return;
    }
  struct ListNode *current_left = left, *current_right = right;
  struct ListNode *prev_left = left;
  while (current_left != right) {
    if (current_left->val < current_right->val) {
      prev_left = current_left;
      printf("prev_left = %p\n\n", (void *) prev_left);
      if (current_left->next == right) {
        current_left->next = current_right;
        current_left = right;
      } else {
        current_left = current_left->next;
        printf("next\n\n");
      }
    } else {
      prev_left->next = current_right;
      current_right->next = current_left;
      prev_left = current_right;
      current_right = current_right->next;
    }
  }
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


static struct ListNode *sortList(struct ListNode *head) {
  unsigned len = getLen(head);
  for (unsigned width = 1; width < len; width *= 2) {
    for (unsigned i = 0; i < len; i += 2 * width) {
        printf("index 1 = %u, index 2 = %u\n\n", i, i + width);
      merge(get(head, i), get(head, i + width));
      printList(head);
    }
  }
  return head;
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

int main() {
    int array[] = {4, 2, 1, 3};
    unsigned arrayLen = sizeof(array) / sizeof(arrayLen);
    struct ListNode *head = buildList(array, arrayLen);
    printList(head);
    sortList(head);
    printList(head);
    freeList(head);
}

