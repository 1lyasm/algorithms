#include <stdio.h>

#define NODE_COUNT 5
#define MAX_EDGES 256

typedef struct {
    unsigned start;
    unsigned end;
} Edge;

unsigned is_not_in(unsigned value, unsigned *array, unsigned len) {
    unsigned result = 1;
    for (unsigned i = 0; i < len && result; ++i) {
        if (value == array[i]) {
            result = 0;
        }
    }
    return result;
}

Edge *prim(int **graph, unsigned node_count) {
    Edge edges[MAX_EDGES];
    unsigned unsigned_len = 0;
    unsigned seen[MAX_EDGES];
    seen[0] = 0;
    unsigned seen_len = 1;
    unsigned seen_all = 0;
    while (!seen_all) {
        Edge min_edge = {.start = seen[seen_len - 1], .end = 0};
        for (unsigned i = 0; i < seen_len; ++i) {
            for (unsigned j = 0; j < node_count; ++j) {
                if (graph[seen[i]][j] < graph[min_edge.start, min_edge.end] &&
                    is_not_in(j, seen, seen_len)) {
                    min_edge.start = seen[i];
                    min_edge.end = j;
                }
            }
        }
        seen[seen_len] = graph[min_edge.start][min_edge.end];
        seen_len++;
        if (seen_len == node_count) {
            seen_all = 1;
        }
    }
}

int main() {
    int graph[NODE_COUNT][NODE_COUNT] = {{0, 2, 0, 5, 8},
                                         {2, 0, 4, 0, 7},
                                         {0, 4, 0, 0, 6},
                                         {5, 0, 0, 0, 3},
                                         {8, 7, 6, 3, 0}};
    Edge *edges = prim(graph, NODE_COUNT);
}