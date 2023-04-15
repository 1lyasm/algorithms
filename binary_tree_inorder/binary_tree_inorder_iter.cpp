#include "binary_tree_inorder.h"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

class Solution {
public:
  struct StackItem {
    TreeNode *node;
    bool was_visited;
    StackItem(TreeNode *node) : node(node), was_visited(false) {}
  };

  std::vector<int> inorderTraversal(TreeNode *root) {
    std::vector<int> traversal;
    if (root == nullptr) {
      return traversal;
    }
    std::vector<StackItem> stack;
    stack.push_back(StackItem(root));
    while (!stack.empty()) {
      if (!stack.back().was_visited && stack.back().node->left != nullptr) {
        stack.back().was_visited = true;
        stack.push_back(StackItem(stack.back().node->left));
      } else {
        TreeNode *leftMost = stack.back().node;
        traversal.push_back(leftMost->val);
        stack.pop_back();
        if (leftMost->right != nullptr) {
          stack.push_back(StackItem(leftMost->right));
        }
      }
    }
    return traversal;
  }
};
