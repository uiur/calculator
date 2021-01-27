#include "tokenize.h"
#include <stdlib.h>
#include <string.h>

Token* tokenize(char* s) {
  Token* head = (Token*)malloc(sizeof(Token));
  head->symbol = "";

  Token* current = head;

  while (*s != '\0') {
    if (*s == '+' || *s == '*' || *s == '(' || *s == ')') {
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
