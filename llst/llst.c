#include "llst.h"

#include <stdio.h>
#include <stdlib.h>

void build(struct LList *L, int *arr, int asize) {
  L->size = 0;
  L->head = malloc(sizeof(struct Node));
  L->head->item = arr[0];
  L->size++;
  struct Node *cur = L->head;
  struct Node *nxt = NULL;
  for (int i = 1; i < asize; i++) {
    nxt = (struct Node *)malloc(sizeof(struct Node));
    nxt->item = arr[i];
    cur->next = nxt;
    cur = nxt;
    L->size++;
  }
  return;
}

void print(struct LList *L) {
  struct Node *nptr = malloc(sizeof(struct Node));
  nptr = L->head;
  printf("%d ", nptr->item);
  while (nptr->next != NULL) {
    nptr = nptr->next;
    printf("%d ", nptr->item);
  }
  printf("\n");
  return;
}

struct Node *get_at(struct LList *L, int idx) {
  struct Node *tmp = L->head;
  for (int i = 0; i < idx; i++) {
    tmp = tmp->next;
  }
  return tmp;
}
