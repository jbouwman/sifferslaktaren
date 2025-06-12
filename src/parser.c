#include <stdio.h>
#include <stdlib.h>
#include "parser.h"

#include "rational.h"

ExprNode* parse_expression(Lexer *lexer) {
  ExprNode *left = parse_term(lexer);
  if (!left) return NULL;
    
  while (lexer->current_token.type == TOKEN_PLUS) {
    TokenType op = lexer->current_token.type;
    lexer_next_token(lexer);
        
    ExprNode *right = parse_term(lexer);
    if (!right) {
      expr_unref(left);
      return NULL;
    }
        
    NodeType node_type = NODE_ADD;
    ExprNode *new_left = expr_create_binary(node_type, left, right);
    expr_unref(left);
    expr_unref(right);
    left = new_left;
        
    if (!left) return NULL;
  }

  while (lexer->current_token.type == TOKEN_MINUS) {
    TokenType op = lexer->current_token.type;
    lexer_next_token(lexer);

    ExprNode *right = parse_term(lexer);
    if (!right) {
      expr_unref(left);
      return NULL;
    }

    NodeType node_type = NODE_SUB;
    ExprNode *new_left = expr_create_binary(node_type, left, right);
    expr_unref(left);
    expr_unref(right);
    left = new_left;

    if (!left) return NULL;
  }
    
  return left;
}

ExprNode* parse_term(Lexer *lexer) {
  return parse_factor(lexer);
}

ExprNode* parse_factor(Lexer *lexer) {
  if (lexer->current_token.type == TOKEN_NUMBER) {
    Rational value = lexer->current_token.value.number;
    lexer_next_token(lexer);
    return expr_create_constant(value);
  }
    
  if (lexer->current_token.type == TOKEN_LPAREN) {
    lexer_next_token(lexer);
    ExprNode *expr = parse_expression(lexer);
    if (!expr) return NULL;
        
    if (lexer->current_token.type != TOKEN_RPAREN) {
      expr_unref(expr);
      return NULL;
    }
    lexer_next_token(lexer);
    return expr;
  }
    
  return NULL;
}

ExprNode* parse_string(const char *input) {
  Lexer lexer;
  lexer_init(&lexer, input);
    
  ExprNode *result = parse_expression(&lexer);
  token_free(&lexer.current_token);
    
  return result;
}
