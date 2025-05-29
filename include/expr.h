#ifndef EXPR_H
#define EXPR_H

typedef enum {
  NODE_CONSTANT,
  NODE_ADD,
  NODE_SUB
} NodeType;

typedef struct ExprNode {
  NodeType type;
  union {
    int value;
    struct {
      struct ExprNode *left;
      struct ExprNode *right;
    } binary;
  } data;
  int refcount;
} ExprNode;

ExprNode* expr_ref(ExprNode *expr);
void expr_unref(ExprNode *expr);

ExprNode* expr_create_constant(int value);
ExprNode* expr_create_binary(NodeType type, ExprNode *left, ExprNode *right);

char* expr_to_string(ExprNode *expr);
int expr_evaluate(ExprNode *expr);

#endif /* EXPR_H */
