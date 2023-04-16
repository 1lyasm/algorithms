#ifndef BINARY_TREE_CODEC_H
#define BINARY_TREE_CODEC_H

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

#endif
