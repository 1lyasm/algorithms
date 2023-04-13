#ifndef CONSTRUCT_BINARY_TREE_H
#define CONSTRUCT_BINARY_TREE_H

struct TreeNode {
  int val;
  struct TreeNode *left;
  struct TreeNode *right;
};

struct TreeNode *buildTree(int *preorder, int preorderSize, int *inorder,
                           int inorderSize);

#endif
