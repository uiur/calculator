#include "parse.h"
#include <stdio.h>

void test(char *s, int expected) {
  int actual = calc(s);
  if (actual != expected) {
    printf("calc(\"%s\")\n  expect: %d\n  actual: %d\n", s, expected, actual);
  }
}

int main(int argc, char **argv) {
  for (int i = 1; i < argc; i++) {
    char *s = argv[i];
    printf("%d\n", calc(s));
  }
  return 0;
}
