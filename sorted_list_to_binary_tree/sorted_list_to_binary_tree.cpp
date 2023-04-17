#include "sorted_list_binary_tree.h"

#include <deque>
#include <vector>

class Solution {
public:
  int list_size(ListNode *head) {
    ListNode *it = head;
    int count = 0;
    while (it) {
      it = it->next;
      ++count;
    }
    return count;
  }

  TreeNode *sortedListToBST(ListNode *head) {
    if (head == nullptr) {
      return nullptr;
    }
    TreeNode *root = new TreeNode();
    int counter = 1;
    std::deque<TreeNode *> parents = {root};
    int nodeCount = list_size(head);
    while (counter < nodeCount) {
      parents.front()->left = new TreeNode();
      parents.push_back(parents.front()->left);
      ++counter;
      if (counter >= nodeCount) {
        break;
      }
      parents.front()->right = new TreeNode();
      parents.push_back(parents.front()->right);
      ++counter;
      if (counter >= nodeCount) {
        break;
      }
      parents.pop_front();
    }
    std::vector<TreeNode *> stack;
    ListNode *list_it = head;
    TreeNode *tree_it = root;
    while (tree_it != nullptr || !stack.empty()) {
      while (tree_it != nullptr) {
        stack.push_back(tree_it);
        tree_it = tree_it->left;
      }
      stack.back()->val = list_it->val;
      list_it = list_it->next;
      tree_it = stack.back();
      stack.pop_back();
      tree_it = tree_it->right;
    }
    return root;
  }
};
