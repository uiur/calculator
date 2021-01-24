#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
  OP_ADD,
  OP_MUL,
  VAL_NUM
} NodeKind;

typedef struct Node {
  NodeKind kind;
  struct Node* left;
  struct Node* right;
  int value;
} Node;

typedef struct Token {
  struct Token* next;
  char* symbol;
} Token;

void next(Token** s) {
  *s = (*s)->next;
}

Node* number(Token** s) {
  char c = *((*s)->symbol);
  if (c >= '0' && c <= '9') {
    int n =  atoi((*s)->symbol);
    next(s);
    Node* node = (Node*)malloc(sizeof(Node));
    node->kind = VAL_NUM;
    node->value = n;
    return node;
  }

  return NULL;
}

int consume_op(Token** s, char op) {
  if (*s != NULL && *((*s)->symbol) == op) {
    next(s);
    return 1;
  }

  return 0;
}

Node* term(Token **s) {
  Node* left = number(s);

  int success = consume_op(s, '*');
  if (!success) {
    return left;
  }

  Node* right = term(s);

  Node* node = (Node*)malloc(sizeof(Node));
  node->kind = OP_MUL;
  node->left = left;
  node->right = right;

  return node;
}

Node* expression(Token **s) {
  Node* left = term(s);

  int success = consume_op(s, '+');
  if (!success) {
    return left;
  }

  Node* right = expression(s);

  Node* node = (Node*)malloc(sizeof(Node));
  node->kind = OP_ADD;
  node->left = left;
  node->right = right;

  return node;
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

Node* parse(Token* token) {
  return expression(&token);
}

void print_node(Node *node) {
  if (node->kind == OP_ADD || node->kind == OP_MUL) {
    char op = node->kind == OP_ADD ? '+' : '*';

    printf("(%c ", op);
    print_node(node->left);
    printf(" ");

    print_node(node->right);
    printf(")");
  }

  if (node->kind == VAL_NUM) {
    printf("%d", node->value);
  }
}

int evaluate(Node* node) {
  if (node->kind == OP_ADD) {
    return evaluate(node->left) + evaluate(node->right);
  }

  if (node->kind == OP_MUL) {
    return evaluate(node->left) * evaluate(node->right);
  }

  if (node->kind == VAL_NUM) {
    return node->value;
  }

  return 0;
}

int calc(char* s) {
  Token* head = tokenize(s);
  // print_tokens(head);
  Node* node = parse(head);
  // print_node(node);
  // puts("");
  return evaluate(node);
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
