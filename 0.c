#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Token {
  struct Token* next;
  char* symbol;
} Token;

void next(Token** s) {
  *s = (*s)->next;
}

int number(Token** s) {
  char c = *((*s)->symbol);
  if (c >= '0' && c <= '9') {
    int n =  atoi((*s)->symbol);
    next(s);
    return n;
  }

  return 0;
}

int consume_op(Token** s, char op) {
  if (*s != NULL && *((*s)->symbol) == op) {
    next(s);
    return 1;
  }

  return 0;
}

int term(Token **s) {
  int left = number(s);

  int success = consume_op(s, '*');
  if (!success) {
    return left;
  }

  int right = term(s);

  return left * right;
}

int expression(Token **s) {
  int left = term(s);

  int success = consume_op(s, '+');
  if (!success) {
    return left;
  }

  int right = expression(s);
  return left + right;
}

Token* tokenize(char* s) {
  Token* head = (Token*)malloc(sizeof(Token));
  head->symbol = "";

  Token* current = head;

  while (*s != '\0') {
    if (*s == '+' || *s == '*') {
      Token* new_token = (Token*)malloc(sizeof(Token));
      new_token->symbol = (char*)malloc(2 * sizeof(char));
      strncpy(new_token->symbol, s, 1);

      current->next = new_token;
      current = new_token;

      s++;
      continue;
    }

    if (*s >= '0' && *s <= '9') {
      Token* new_token = (Token*)malloc(sizeof(Token));

      int size;
      for(size = 1; *(s + size) >= '0' && *(s + size) <= '9'; size++) {}

      new_token->symbol = (char*)malloc((size + 1) * sizeof(char));
      strncpy(new_token->symbol, s, size);

      current->next = new_token;
      current = new_token;

      s += size;
      continue;
    }

    s++;
  }

  return head->next;
}

void print_tokens(Token* head) {
  while (head != NULL) {
    printf("`%s` ", head->symbol);
    head = head->next;
  }
  printf("\n");
}

int calc(char* s) {
  Token* head = tokenize(s);
  // print_tokens(head);
  return expression(&head);
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
