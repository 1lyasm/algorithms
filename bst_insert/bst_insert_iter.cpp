#include "bst_insert.h"

class Solution {
public:
  TreeNode *insertIntoBST(TreeNode *root, int val) {
    if (!root) {
      return new TreeNode(val);
    }
    TreeNode *cur = root;
    while (true) {
      if (val < cur->val) {
        if (!cur->left) {
          cur->left = new TreeNode(val);
          return root;
        }
        cur = cur->left;
      } else {
        if (!cur->right) {
          cur->right = new TreeNode(val);
          return root;
        }
        cur = cur->right;
      }
    }
  }
};
