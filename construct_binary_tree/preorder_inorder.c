#include "preorder_inorder.h"

#include <stdlib.h>

struct HashTable {
  int *arr;
  int min;
  int max;
};

static int hashFunc(struct HashTable *hash, int value) {
  int hashInd;
  if (value >= 0) {
    hashInd = value;
  } else {
    hashInd = hash->max - value;
  }
  if (hash->min > 0) {
    hashInd -= hash->min;
  }
  return hashInd;
}

static void setMaxMin(struct HashTable *hash, int *arr, int len) {
  hash->max = arr[0];
  hash->min = arr[0];
  for (int i = 0; i < len; ++i) {
    if (arr[i] > hash->max) {
      hash->max = arr[i];
    }
    if (arr[i] < hash->min) {
      hash->min = arr[i];
    }
  }
}

static struct TreeNode *buildSubTree(int *restrict pre, int preStart,
                                     int preEnd, int *restrict in, int inStart,
                                     int inEnd, struct HashTable *hash) {
  if (preStart > preEnd) {
    return 0;
  }
  struct TreeNode *restrict root = malloc(sizeof *root);
  root->val = pre[preStart];
  int rootInd = hash->arr[hashFunc(hash, pre[preStart])] - inStart;
  root->left = buildSubTree(pre, preStart + 1, preStart + rootInd, in, inStart,
                            inStart + rootInd - 1, hash);
  root->right = buildSubTree(pre, preStart + rootInd + 1, preEnd, in,
                             inStart + rootInd + 1, inEnd, hash);
  return root;
}

struct TreeNode *buildTree(int *restrict preorder, int preorderSize,
                           int *restrict inorder, int inorderSize) {
  struct HashTable hash;
  setMaxMin(&hash, inorder, inorderSize);
  hash.arr = malloc(sizeof *hash.arr * (size_t)(hash.max - hash.min + 1));
  for (int i = 0; i < inorderSize; ++i) {
    hash.arr[hashFunc(&hash, inorder[i])] = i;
  }
  struct TreeNode *root = buildSubTree(preorder, 0, preorderSize - 1, inorder,
                                       0, inorderSize - 1, &hash);
  free(hash.arr);
  return root;
}
