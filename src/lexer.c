#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "lexer.h"

void lexer_init(Lexer *lexer, const char *input) {
    lexer->input = input;
    lexer->position = 0;
    lexer_next_token(lexer);
}

static void skip_whitespace(Lexer *lexer) {
    while (lexer->input[lexer->position] && isspace(lexer->input[lexer->position])) {
        lexer->position++;
    }
}

static int read_number(Lexer *lexer) {
    int value = 0;
    while (isdigit(lexer->input[lexer->position])) {
        value = value * 10 + (lexer->input[lexer->position] - '0');
        lexer->position++;
    }
    return value;
}

void lexer_next_token(Lexer *lexer) {
    skip_whitespace(lexer);
    
    char current_char = lexer->input[lexer->position];
    
    if (current_char == '\0') {
        lexer->current_token.type = TOKEN_EOF;
        return;
    }
    
    if (isdigit(current_char)) {
        lexer->current_token.type = TOKEN_NUMBER;
        lexer->current_token.value.number = read_number(lexer);
        return;
    }
    
    switch (current_char) {
        case '+':
            lexer->current_token.type = TOKEN_PLUS;
            lexer->position++;
            break;
        case '-':
            lexer->current_token.type = TOKEN_MINUS;
            lexer->position++;
            break;
        case '(':
            lexer->current_token.type = TOKEN_LPAREN;
            lexer->position++;
            break;
        case ')':
            lexer->current_token.type = TOKEN_RPAREN;
            lexer->position++;
            break;
        default:
            lexer->current_token.type = TOKEN_ERROR;
            lexer->position++;
            break;
    }
}

void token_free(Token *token) {
}
