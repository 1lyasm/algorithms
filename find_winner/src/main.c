#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int no;
    int h;
    int m;
    int s;
} Player;

Player *compare(Player *p1, Player *p2) {
    int p1Sec = p1->h * 3600 + p1->m * 60 + p1->s;
    int p2Sec = p2->h * 3600 + p2->m * 60 + p2->s;
    if (p1Sec > p2Sec) {
        return p2;
    } else if (p1Sec == p2Sec) {
        return p2;
    } else if (p1Sec < p2Sec) {
        return p1;
    }
    return NULL;
}

Player *findWinner(Player *players, int start, int end) {
    // printf("findWinner: called: start: %d, end: %d\n", start, end);
    int mid;
    if (start == end) {
        return &players[start];
    }
    mid = (start + end) / 2;
    return compare(findWinner(players, start, mid),
                   findWinner(players, mid + 1, end));
}

void printPlayer(Player *p) {
    printf("{no: %d, h: %d, m: %d, s: %d}", p->no, p->h, p->m, p->s);
}

void printPlayers(Player *players, int n) {
    int i;
    for (i = 0; i < n; ++i) {
        printPlayer(&players[i]);
        printf("\n");
    }
}

int main() {
    {
        Player players[] = {{2, 1, 10, 23},
                            {4, 1, 8, 15},
                            {6, 1, 12, 39},
                            {3, 0, 9, 19},
                            {14, 0, 58, 59}};
        int n = sizeof(players) / sizeof(players[0]);
        printPlayers(players, n);
        printf("winner: %d\n\n", findWinner(players, 0, n - 1)->no);
    }
    {
        Player players[] = {{5, 1, 2, 3},
                            {4, 2, 3, 4},
                            {3, 3, 4, 5},
                            {2, 4, 5, 6},
                            {1, 5, 6, 7}};
        int n = sizeof(players) / sizeof(players[0]);
        printPlayers(players, n);
        printf("winner: %d\n\n", findWinner(players, 0, n - 1)->no);
    }
    {
        Player players[] = {{5, 5, 6, 7},
                            {4, 4, 5, 6},
                            {3, 3, 4, 5},
                            {2, 2, 3, 4},
                            {1, 1, 2, 3}};
        int n = sizeof(players) / sizeof(players[0]);
        printPlayers(players, n);
        printf("winner: %d\n\n", findWinner(players, 0, n - 1)->no);
    }
}
