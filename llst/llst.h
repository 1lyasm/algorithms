#ifndef LLST_H
#define LLST_H

struct Node {
  int item;
  struct Node *next;
};
struct LList {
  struct Node *head;
  int size;
};
void build(struct LList *L, int *arr, int asize);
void print(struct LList *L);
struct Node *get_at(struct LList *L, int idx);

#endif
