#include <stdio.h>
#include <stdlib.h>

void fail(char *msg) {
    fprintf(stderr, "%s", msg);
    exit(EXIT_FAILURE);
}

typedef struct {
    int value;
    int priority;
} Node;

typedef struct {
    Node *array[256];
    unsigned len;
} PriorityQueue;

unsigned is_empty(PriorityQueue *pq) {
    unsigned result = 1;
    if (pq->len) {
        result = 0;
    }
    return result;
}

void insert_with_priority(PriorityQueue *pq, Node *node) {
    pq->array[pq->len] = node;
    pq->len++;
}

Node *pull_highest_priority(PriorityQueue *pq) {
    if (!pq->len) {
        return NULL;
    }
    Node *highest = pq->array[0];
    unsigned highest_index = 0;
    for (unsigned i = 0; i < pq->len; ++i) {
        if (pq->array[i]->priority > highest->priority) {
            highest = pq->array[i];
            highest_index = i;
        }
    }
    pq->array[highest_index] = pq->array[pq->len - 1];
    --(pq->len);
    return highest;
}

void print(PriorityQueue *pq) {
    printf("pq: ");
    for (unsigned i = 0; i < pq->len; ++i) {
        printf("{ .value = %d, .priority = %d } ", pq->array[i]->value,
               pq->array[i]->priority);
    }
    printf("\n");
}

PriorityQueue *alloc_priority_queue() {
    PriorityQueue *pq = malloc(sizeof(PriorityQueue));
    if (!pq) {
        fail("alloc_priority_queue: malloc failed");
    }
    pq->len = 0;
    return pq;
}

void free_priority_queue(PriorityQueue *pq) { free(pq); }

int main() {
    PriorityQueue *pq = alloc_priority_queue();

    print(pq);
    printf("is_empty: %u\n", is_empty(pq));
    Node node = {.value = 1, .priority = 7};
    insert_with_priority(pq, &node);
    print(pq);
    printf("is_empty: %u\n", is_empty(pq));
    Node node_2 = {.value = 2, .priority = 8};
    insert_with_priority(pq, &node_2);
    print(pq);
    Node *highest = pull_highest_priority(pq);
    printf("highest: value: %d, priority: %d\n", highest->value,
           highest->priority);
    print(pq);
    Node node_3 = {.value = 0, .priority = 0};
    insert_with_priority(pq, &node_3);
    print(pq);
    highest = pull_highest_priority(pq);
    printf("highest: value: %d, priority: %d\n", highest->value,
           highest->priority);
    print(pq);

    free_priority_queue(pq);
}
