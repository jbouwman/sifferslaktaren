#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test.h"
#include "lexer.h"

int main(void) {
    printf("test: lexer\n");
    
    Lexer lexer;

    lexer_init(&lexer, "42");
    ASSERT(lexer.current_token.type == TOKEN_NUMBER, "Number token type");
    ASSERT(lexer.current_token.value.number == 42, "Number token value");
    
    lexer_next_token(&lexer);
    ASSERT(lexer.current_token.type == TOKEN_EOF, "EOF after number");
    
    lexer_init(&lexer, "+");
    ASSERT(lexer.current_token.type == TOKEN_PLUS, "Plus token");
    
    lexer_init(&lexer, "(");
    ASSERT(lexer.current_token.type == TOKEN_LPAREN, "Left paren token");
    
    lexer_init(&lexer, ")");
    ASSERT(lexer.current_token.type == TOKEN_RPAREN, "Right paren token");
    
    lexer_init(&lexer, "123 + 456");
    ASSERT(lexer.current_token.type == TOKEN_NUMBER, "First number");
    ASSERT(lexer.current_token.value.number == 123, "First number value");
    
    lexer_next_token(&lexer);
    ASSERT(lexer.current_token.type == TOKEN_PLUS, "Plus operator");
    
    lexer_next_token(&lexer);
    ASSERT(lexer.current_token.type == TOKEN_NUMBER, "Second number");
    ASSERT(lexer.current_token.value.number == 456, "Second number value");
    
    lexer_next_token(&lexer);
    ASSERT(lexer.current_token.type == TOKEN_EOF, "EOF at end");

    lexer_init(&lexer, "42$");
    ASSERT(lexer.current_token.type == TOKEN_NUMBER, "Number before error");
    
    lexer_next_token(&lexer);
    ASSERT(lexer.current_token.type == TOKEN_ERROR, "Error token for invalid character");
    
    return EXIT_SUCCESS;
}
