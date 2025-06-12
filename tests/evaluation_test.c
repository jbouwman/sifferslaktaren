#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test.h"
#include "parser.h"

int main(void) {
  printf("test: evaluation\n");
    
  ExprNode *expr = parse_string("1 - 2 + 3");
  ASSERT(expr_evaluate(expr) == 2,
         "Simple expression containing addition and subtraction tems evaluates to 2");
  return EXIT_SUCCESS;
}
