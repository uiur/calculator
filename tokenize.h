typedef struct Token {
  struct Token* next;
  char* symbol;
} Token;

Token* tokenize(char* s);
