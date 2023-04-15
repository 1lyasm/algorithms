#include "binary_tree_inorder.h"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

class Solution {
public:
  std::vector<int> inorderTraversal(TreeNode *root) {
    std::vector<int> traversal;
    std::vector<TreeNode *> stack;
    TreeNode *cur = root;
    while (cur != nullptr || !stack.empty()) {
      while (cur != nullptr) {
        stack.push_back(cur);
        cur = cur->left;
      }
      traversal.push_back(stack.back()->val);
      cur = stack.back();
      stack.pop_back();
      cur = cur->right;
    }
    return traversal;
  }
};
