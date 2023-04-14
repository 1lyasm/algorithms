#include "bst_delete.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct TreeNode *deleteNode(struct TreeNode *root, int key) {
  if (root == 0) {
    return root;
  }
  struct TreeNode *deleted = root;
  struct TreeNode *deletedParent = root;
  while (deleted->val != key) {
    deletedParent = deleted;
    if (key < deleted->val) {
      deleted = deleted->left;
    } else {
      deleted = deleted->right;
    }
    if (deleted == 0) {
      return root;
    }
  }
  struct TreeNode *newChild = deleted->right;
  struct TreeNode *newRoot = root;
  if (newChild == 0) {
    newChild = deleted->left;
  } else {
    struct TreeNode *rMin = deleted->right;
    while (rMin->left != 0) {
      rMin = rMin->left;
    }
    rMin->left = deleted->left;
  }
  if (deletedParent->left == deleted) {
    deletedParent->left = newChild;
  } else {
    deletedParent->right = newChild;
  }
  if (deleted == root) {
    newRoot = newChild;
  }
  free(deleted);
  return newRoot;
}
