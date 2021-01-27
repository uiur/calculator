#include "parse.h"
#include <stdio.h>

int failed = 0;

int test(char *s, int expected) {
  int actual = calc(s);
  if (actual != expected) {
    printf("calc(\"%s\")\n  expect: %d\n  actual: %d\n", s, expected, actual);
    failed = 1;
  }

  return actual == expected;
}

int main(int argc, char **argv) {
  test("1 + 2", 3);
  test("10 + 20", 30);
  test("2 * 3", 6);
  test("1 + 2 * 3", 7);
  test("2 * 2 + 3", 7);
  test("3", 3);
  test("1234", 1234);
  test("(1 + 2) * 3", 9);
  if (!failed) {
    printf("all tests succeeded\n");
  }

  return failed;
}
