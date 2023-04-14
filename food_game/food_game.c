#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

static void takeInp(long *n, long *m) {
  char buf[1024], *end;
  do {
    printf("N ve M-i gir: ");
    do {
      fgets(buf, sizeof(buf), stdin);
    } while (buf[0] == '\n');
    errno = 0;
  } while (((*n = strtol(buf, &end, 10)) == 0 ||
            (*m = strtol(end, &end, 10)) == 0 || errno == ERANGE) &&
           printf("Invalid input, try again\n"));
}

static void foodGame(void) {
  long n, m;
  takeInp(&n, &m);
  printf("n: %ld, m: %ld\n", n, m);
}

int main() {
  foodGame();
  return 0;
}
