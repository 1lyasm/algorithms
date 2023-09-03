#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void err(char *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(EXIT_FAILURE);
}

int main() {
    const int maxCnt = 1024;
    char *inp = malloc(maxCnt * sizeof(char));
    if (!inp) err("main: malloc failed");
    if (!fgets(inp, maxCnt, stdin)) err("main: fgets failed");
    int j = 0;
    char prefix[] = "gh repo clone ";
    int prefixLen = strlen(prefix);
    for (int i = 0; i < strlen(inp); ++i) {
        if (inp[i] == ' ' || inp[i] == '\n') {
            int repoNameLen = i - j, cmdLen = prefixLen + repoNameLen;
            char *cmd = malloc((cmdLen + 1) * sizeof(char));
            if (!cmd) err("main: malloc failed");
            cmd[cmdLen] = 0;
            memcpy(cmd, prefix, prefixLen * sizeof(char));
            memcpy(cmd + prefixLen, inp + j, repoNameLen * sizeof(char));
            system(cmd);
            free(cmd);
            j = i + 1;
        }
    }
    free(inp);
    return 0;
}
