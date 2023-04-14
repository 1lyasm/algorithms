#include <stdio.h>

void ignore_ws(char *s, int *pos) {
  while (s[*pos] == ' ')
    ++*pos;
}

int myAtoi(char *s) {
  int pos = 0;
  ignore_ws(s, &pos);
  handle_sign();
  printf("pos: %d", pos);
  return -1;
}

int main() {
  myAtoi(" oy");
  return 0;
}
