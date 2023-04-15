#include "binary_tree_inorder.h"
#include <vector>
using namespace std;

class Solution {
public:
  vector<int> inorderTraversal(TreeNode *root) {
    if (!root) {
      return vector<int>();
    }
    vector<int> left_traversal = inorderTraversal(root->left);
    left_traversal.push_back(root->val);
    vector<int> right_traversal = inorderTraversal(root->right);
    left_traversal.insert(left_traversal.end(), right_traversal.begin(),
                          right_traversal.end());
    return left_traversal;
  }
};
