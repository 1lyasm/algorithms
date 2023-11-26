#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N_MODE 2

typedef enum { Normal, Debug } Mode;

Mode parseMode(char *arg) {
    // if (strcmp(argv[1], "NORMAL") != 0 && strcmp(argc[1]))
    // TODO return something
}

Mode parseArgs(int argc, char **argv) {
    char *modes[N_MODE] = {"NORMAL", "DEBUG"};
    char *modeArg;
    if (argc != 2) {
        printf("Program için 1 parametre gerekli: NORMAL ve ya DEBUG\n");
        exit(EXIT_FAILURE);
    }
    modeArg = argv[1];
    return parseMode(modeArg);
}

int main(int argc, char **argv) {
    parseArgs(argc, argv);
    // TODO print something
    return 0;
}
