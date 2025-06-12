#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test.h"
#include "expr.h"

int main(void) {
  printf("Test: expr\n");
    
  ExprNode *const_node = expr_create_constant(42);

  ASSERT(const_node != NULL, "Constant creation");
  ASSERT(const_node->type == NODE_CONSTANT, "Constant type");
  ASSERT(const_node->data.value == 42, "Constant value");
  ASSERT(const_node->refcount == 1, "Initial refcount");
    
  int result = expr_evaluate(const_node);
  ASSERT(result == 42, "Constant evaluation");
    
  char *str = expr_to_string(const_node);
  ASSERT_STRCMP(str, "42", "Constant string");
  free(str);

  // Test operations
  
  ExprNode *const_node2 = expr_create_constant(8);
  ExprNode *operation_node;
  
  // Addition
    
  operation_node = expr_create_binary(NODE_ADD, const_node, const_node2);

  ASSERT(operation_node != NULL,
         "Addition creation");
  ASSERT(operation_node->type == NODE_ADD,
         "Addition type");
  ASSERT(operation_node->data.binary.left == const_node,
         "Addition left operand");
  ASSERT(operation_node->data.binary.right == const_node2,
         "Addition right operand");
    
  result = expr_evaluate(operation_node);
  ASSERT(result == 50, "Addition evaluation");

  str = expr_to_string(operation_node);
  ASSERT_STRCMP(str, "(42 + 8)", "Addition string representation");

  free(str);

  // Subtraction
    
  operation_node = expr_create_binary(NODE_SUB, const_node, const_node2);

  ASSERT(operation_node != NULL,
         "Subtraction creation");
  ASSERT(operation_node->type == NODE_SUB,
         "Subtraction type");
  ASSERT(operation_node->data.binary.left == const_node,
         "Subtraction left operand");
  ASSERT(operation_node->data.binary.right == const_node2,
         "Subtraction right operand");
    
  result = expr_evaluate(operation_node);
  ASSERT(result == 34, "Subtraction evaluation");

  str = expr_to_string(operation_node);
  ASSERT_STRCMP(str, "(42 - 8)", "Subtraction string representation");

  free(str);
  
  return EXIT_SUCCESS;
}
