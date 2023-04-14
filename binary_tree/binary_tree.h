#ifndef BINARY_TREE_H
#define BINARY_TREE_H

struct BinTree {
  void *item;
  BinTree *left;
  BinTree *parent;
  BinTree *right;
};

#endif
