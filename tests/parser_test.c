#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test.h"
#include "parser.h"

int main(void) {
    printf("test: parser\n");
    
    ExprNode *expr = parse_string("42");
    ASSERT(expr != NULL, "Parse simple number");
    ASSERT(expr->type == NODE_CONSTANT, "Simple number type");
    ASSERT(expr->data.value == 42, "Simple number value");
    expr_unref(expr);
    
    expr = parse_string("5 + 3");
    ASSERT(expr != NULL, "Parse simple addition");
    ASSERT(expr->type == NODE_ADD, "Addition type");
    ASSERT(expr->data.binary.left->type == NODE_CONSTANT, "Addition left type");
    ASSERT(expr->data.binary.left->data.value == 5, "Addition left value");
    ASSERT(expr->data.binary.right->type == NODE_CONSTANT, "Addition right type");
    ASSERT(expr->data.binary.right->data.value == 3, "Addition right value");
    
    int result = expr_evaluate(expr);
    ASSERT(result == 8, "Addition evaluation");
    expr_unref(expr);
    
    expr = parse_string("(5 + 3)");
    ASSERT(expr != NULL, "Parse parentheses");
    ASSERT(expr->type == NODE_ADD, "Parentheses type");
    
    result = expr_evaluate(expr);
    ASSERT(result == 8, "Parentheses evaluation");
    expr_unref(expr);

    expr = parse_string("5 +");
    ASSERT(expr == NULL, "Incomplete expression");
    
    expr = parse_string("(5 + 3");
    ASSERT(expr == NULL, "Unmatched parentheses");
    
    return EXIT_SUCCESS;
}
