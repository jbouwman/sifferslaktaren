#ifndef LEXER_H
#define LEXER_H

#include "rational.h"

typedef enum {
  TOKEN_NUMBER,
  TOKEN_PLUS,        // +
  TOKEN_MINUS,       // -
  TOKEN_LPAREN,      // (
  TOKEN_RPAREN,      // )
  TOKEN_EOF,         // End of input
  TOKEN_ERROR
} TokenType;

typedef struct {
  TokenType type;
  union {
    Rational number;
  } value;
} Token;

typedef struct {
  const char *input;
  int position;
  Token current_token;
} Lexer;

void lexer_init(Lexer *lexer, const char *input);
void lexer_next_token(Lexer *lexer);
void skip_whitespace(Lexer *lexer);

void token_free(Token *token);

int is_digit(char c);

#endif /* LEXER_H */
