#ifndef PARSER_H
#define PARSER_H

#include "expr.h"
#include "lexer.h"

ExprNode* parse_expression(Lexer *lexer);
ExprNode* parse_term(Lexer *lexer);
ExprNode* parse_factor(Lexer *lexer);

ExprNode* parse_string(const char *input);

#endif /* PARSER_H */
