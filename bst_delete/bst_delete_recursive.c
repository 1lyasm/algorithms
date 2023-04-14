#include "bst_delete.h"
#include <stdlib.h>

struct TreeNode *deleteSubnode(struct TreeNode *root, int key) {
  struct TreeNode *nextTree;
  if (key < root->val) {
    nextTree = root->left;
  } else if (key > root->val) {
    nextTree = root->right;
  }
  return deleteSubnode(nextTree, key);
}

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

  
}
