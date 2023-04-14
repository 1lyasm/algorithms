#ifndef BST_DELETE_H
#define BST_DELETE_H

struct TreeNode {
  int val;
  struct TreeNode *left;
  struct TreeNode *right;
};

struct TreeNode *deleteNode(struct TreeNode *root, int key);

#endif
