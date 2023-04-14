#include "bst_delete.h"

class Solution {
public:
  TreeNode *deleteNode(TreeNode *root, int key) {
    if (root == nullptr) {
      return root;
    }
    TreeNode *deleted = root;
    TreeNode *deletedParent = root;
    while (deleted->val != key) {
      deletedParent = deleted;
      if (key < deleted->val) {
        deleted = deleted->left;
      } else {
        deleted = deleted->right;
      }
      if (deleted == nullptr) {
        return root;
      }
    }
    TreeNode *newChild = deleted->right;
    TreeNode *newRoot = root;
    if (newChild == nullptr) {
      newChild = deleted->left;
    } else {
      TreeNode *rMin = deleted->right;
      while (rMin->left != nullptr) {
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
    return newRoot;
  }
};
