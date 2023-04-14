#include "bst_delete.h"

class Solution {
public:
  struct TreeNode *deleteNode(struct TreeNode *root, int key) {
    if (root == nullptr) {
      return nullptr;
    }
    if (key < root->val) {
      root->left = deleteNode(root->left, key);
    } else if (key > root->val) {
      root->right = deleteNode(root->right, key);
    } else {
      if (root->left == nullptr) {
        return root->right;
      } else if (root->right == nullptr) {
        return root->left;
      }
      struct TreeNode *cur = root->right;
      while (cur->left != nullptr) {
        cur = cur->left;
      }
      root->val = cur->val;
      root->right = deleteNode(root->right, root->val);
    }
    return root;
  }
};
