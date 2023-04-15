#include "bst_search.h"

struct Solution {
  TreeNode *searchBST(TreeNode *root, int val) {
    TreeNode *cur = root;
    while (cur) {
      if (val < cur->val) {
        cur = cur->left;
      } else if (val > cur->val) {
        cur = cur->right;
      } else {
        return cur;
      }
    }
    return cur;
  }
};
