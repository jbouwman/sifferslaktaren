#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "expr.h"

// Memory management

ExprNode* expr_ref(ExprNode *expr) {
  if (expr) {
    expr->refcount++;
  }
  return expr;
}

void expr_unref(ExprNode *expr) {
  if (!expr) return;
    
  expr->refcount--;
  if (expr->refcount <= 0) {
    // Free children first
    switch (expr->type) {
    case NODE_ADD:
      expr_unref(expr->data.binary.left);
      expr_unref(expr->data.binary.right);
      break;
    case NODE_SUB:
      expr_unref(expr->data.binary.left);
      expr_unref(expr->data.binary.right);
      break;
    case NODE_CONSTANT:
      // No children to free
      break;
    }
    free(expr);
  }
}

ExprNode* expr_create_constant(int value) {
  ExprNode *node = malloc(sizeof(ExprNode));
  if (!node) return NULL;
    
  node->type = NODE_CONSTANT;
  node->data.value = value;
  node->refcount = 1;
  return node;
}

ExprNode* expr_create_binary(NodeType type, ExprNode *left, ExprNode *right) {
  if ((type != NODE_ADD) && (type != NODE_SUB)) {
    return NULL;
  }
    
  ExprNode *node = malloc(sizeof(ExprNode));
  if (!node) return NULL;
    
  node->type = type;
  node->data.binary.left = expr_ref(left);
  node->data.binary.right = expr_ref(right);
  node->refcount = 1;
  return node;
}

int expr_evaluate(ExprNode *expr) {
  if (!expr) return 0;
    
  switch (expr->type) {
  case NODE_CONSTANT:
    return expr->data.value;
            
  case NODE_ADD:
    return expr_evaluate(expr->data.binary.left) +
      expr_evaluate(expr->data.binary.right);

  case NODE_SUB:
    return expr_evaluate(expr->data.binary.left) -
      expr_evaluate(expr->data.binary.right);
                   
  default:
    return 0;
  }
}

char* expr_to_string(ExprNode *expr) {
  if (!expr) return NULL;
    
  char *result = malloc(256);
  if (!result) return NULL;
    
  switch (expr->type) {
  case NODE_CONSTANT:
    snprintf(result, 256, "%d", expr->data.value);
    break;
            
  case NODE_ADD: {
    char *left_str = expr_to_string(expr->data.binary.left);
    char *right_str = expr_to_string(expr->data.binary.right);
    snprintf(result, 256, "(%s + %s)", left_str, right_str);
    free(left_str);
    free(right_str);
    break;
  }

  case NODE_SUB: {
    char *left_str = expr_to_string(expr->data.binary.left);
    char *right_str = expr_to_string(expr->data.binary.right);
    snprintf(result, 256, "(%s - %s)", left_str, right_str);
    free(left_str);
    free(right_str);
    break;
  }
        
  default:
    snprintf(result, 256, "?");
    break;
  }
    
  return result;
}
