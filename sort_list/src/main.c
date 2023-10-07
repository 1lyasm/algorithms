#include <stdio.h>

struct ListNode {
  int val;
  struct ListNode *next;
};

typedef struct ListNode ListNode;

unsigned getLen(ListNode *head) {
    unsigned len = 0;
    ListNode *current = head;
    while (current) {
        current = current->next;
        ++len;
    }
    return len;
}

ListNode *get(ListNode *head, unsigned index) {
    ListNode *current = head;
    for (unsigned i = 0; i <= index; ++i) {
        current = current->next;
    }
    return current;
}

void merge(ListNode *left, ListNode *right) {
    ListNode *current_left = left,
             *current_right = right;
    ListNode *prev_left = 0, *prev_right = 0;
    while (current_left != right) {
        if (current_left->val < current_right->val) {
            prev_left = current_left;
            current_left = current_left->next;
        } else {
            prev_left->next = right;
            current_right->next = left;
            prev_left = right;
            current_right = current_right->next;
        }
    }
}

ListNode *sortList(ListNode *head) {
    unsigned len = getLen(head);
    for (unsigned width = 1; width < len; width *= 2) {
        for (int i = 0; i < len; i += 2 * width) {
            merge(get(head, i), get(head, i + width));
        }
    }
    return head;
}

int main() {}

