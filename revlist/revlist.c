#include "llst.h"
#include <stdlib.h>

void reorder(struct LList *L) {
  int n = L->size / 2;
  struct Node *lft;
  struct Node *mdl;
  struct Node *rgt;
  struct Node *fpart_last_ptr;
  rgt = get_at(L, n - 1);
  fpart_last_ptr = rgt;
  rgt = rgt->next;
  for (int i = 0; i < n; i++) {
    mdl = rgt;
    rgt = rgt->next;
    mdl->next = (i > 0) ? lft : (void *)0;
    lft = mdl;
  }
  fpart_last_ptr->next = mdl;
  return;
}

int main() {
  int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  struct LList L;
  build(&L, arr, 10);
  print(&L);
  reorder(&L);
  print(&L);
  return 0;
}