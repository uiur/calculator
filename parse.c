#include "tokenize.h"
#include "parse.h"
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

Node* expression(Token **s);

void next(Token** s) {
  *s = (*s)->next;
}

int consume(Token** s, char op) {
  if (*s != NULL && *((*s)->symbol) == op) {
    next(s);
    return 1;
  }

  return 0;
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

Node* primary(Token** s) {
  if (consume(s, '(')) {
    Node* e = expression(s);
    consume(s, ')');

    return e;
  }

  return number(s);
}


Node* term(Token **s) {
  Node* left = primary(s);

  int success = consume(s, '*');
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

  int success = consume(s, '+');
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
