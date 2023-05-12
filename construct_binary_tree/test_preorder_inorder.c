#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "preorder_inorder.h"

#define INVALID_VAL 3001

struct Queue {
  struct TreeNode **arr;
  int len;
  int start;
};

static struct TreeNode *pop_front(struct Queue *q) {
  if (q->len < 1) {
    assert(1 == 0);
  }
  --q->len;
  return q->arr[q->start++];
}

static void push_back(struct Queue *q, struct TreeNode *val) {
  q->arr[q->start + q->len++] = val;
}

int main(void) {
  int pre[] = {3, 9, 20, 15, 7};
  int in[] = {9, 3, 15, 20, 7};
  struct TreeNode *outp = buildTree(pre, sizeof(pre) / sizeof(in[0]), in,
                                    sizeof(in) / sizeof(in[0]));
  int expected[] = {3, 9, 20, INVALID_VAL, INVALID_VAL, 15, 7};
  struct Queue q;
  int i;
  q.arr = malloc(1024 * sizeof(struct TreeNode *));
  q.len = 0;
  q.start = 0;
  push_back(&q, outp);
  for (i = 0; q.len > 0;) {
    struct TreeNode *parent = pop_front(&q);
    if (parent->left == 0 && parent->right == 0) {
      i += 2;
      continue;
    }
    push_back(&q, parent->left);
    push_back(&q, parent->right);
    if (parent->left != 0) {
      assert(parent->left->val == expected[++i]);
    } else {
      assert(expected[++i] == INVALID_VAL);
    }
    if (parent->right != 0) {
      assert(parent->right->val == expected[++i]);
    } else {
      assert(expected[++i] == INVALID_VAL);
    }
  }
  free(q.arr);
  printf("\n\nPASSED\n\n");
  return 0;
}
