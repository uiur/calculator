#include "parse.h"
#include <stdio.h>

void test(char *s, int expected) {
  int actual = calc(s);
  if (actual != expected) {
    printf("calc(\"%s\")\n  expect: %d\n  actual: %d\n", s, expected, actual);
  }
}

int main() {
  test("1 + 2", 3);
  test("10 + 20", 30);
  test("2 * 3", 6);
  test("1 + 2 * 3", 7);
  test("2 * 2 + 3", 7);
  test("3", 3);
  test("1234", 1234);
}
