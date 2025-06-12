#include <stdlib.h>
#include <string.h>
#include "lexer.h"

void lexer_init(Lexer *lexer, const char *input) {
  lexer->input = input;
  lexer->position = 0;
  lexer_next_token(lexer);
}

int is_digit(char c) {
  return c >= '0' && c <= '9';
}

void skip_whitespace(Lexer *lexer) {
  while (lexer->input[lexer->position] == ' ' || 
         lexer->input[lexer->position] == '\t' || 
         lexer->input[lexer->position] == '\n' || 
         lexer->input[lexer->position] == '\r') {
    lexer->position++;
  }
}

void lexer_next_token(Lexer *lexer) {
  skip_whitespace(lexer);
    
  char c = lexer->input[lexer->position];
    
  
  if (c == '\0') {
    lexer->current_token.type = TOKEN_EOF;
    return;
  }
  
  switch (c) {
  case '+':
    lexer->current_token.type = TOKEN_PLUS;
    lexer->position++;
    return;
  case '-':
    lexer->current_token.type = TOKEN_MINUS;
    lexer->position++;
    return;
  case '(':
    lexer->current_token.type = TOKEN_LPAREN;
    lexer->position++;
    return;
  case ')':
    lexer->current_token.type = TOKEN_RPAREN;
    lexer->position++;
    return;
  }
  
  if (is_digit(c)) {
    int start = lexer->position;
    long numerator = 0;
        
    
    while (is_digit(lexer->input[lexer->position])) {
      numerator = numerator * 10 + (lexer->input[lexer->position] - '0');
      lexer->position++;
    }
        
    if (lexer->input[lexer->position] == '.') {
      lexer->position++; 
      
      long denominator = 1;
      while (is_digit(lexer->input[lexer->position])) {
        numerator = numerator * 10 + (lexer->input[lexer->position] - '0');
        denominator *= 10;
        lexer->position++;
      }
      
      lexer->current_token.type = TOKEN_NUMBER;
      lexer->current_token.value.number = rational_create(numerator, denominator);
    } else {
      
      lexer->current_token.type = TOKEN_NUMBER;
      lexer->current_token.value.number = rational_create(numerator, 1);
    }
        
    return;
  }
  
  lexer->current_token.type = TOKEN_ERROR;
  lexer->position++;
}

void token_free(Token *token) {
}
