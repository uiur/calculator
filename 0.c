#include <stdio.h>

int number(char** s) {
  if (**s >= '0' && **s <= '9') {
    int n = (**s) - '0';
    (*s)++;
    while (**s >= '0' && **s <= '9') {
      n *= 10;
      n += (**s) - '0';
      (*s)++;
    }
    return n;
  }

  return 0;
}

void next_symbol(char** s) {
  while (**s == ' ') {
    *s += 1;
  }
}


char consume_op(char** s, char op) {
  char c = **s;
  if (c == op) {
    (*s)++;
    return c;
  }

  return '\0';

}

int term(char **s) {
  next_symbol(s);
  int left = number(s);
  next_symbol(s);
  char op = consume_op(s, '*');
  if (op == '\0') {
    return left;
  }

  int right = term(s);

  return left * right;
}

int expression(char **s) {
  next_symbol(s);
  int left = term(s);

  next_symbol(s);
  char op = consume_op(s, '+');
  if (op == '\0') {
    return left;
  }

  next_symbol(s);

  int right = expression(s);

  if (op == '+') {
    return left + right;
  }
  return -1;
}

int calc(char* s) {
  return expression(&s);
}

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
