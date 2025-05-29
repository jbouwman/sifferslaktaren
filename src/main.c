#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "expr.h"
#include "lexer.h"
#include "parser.h"

#define MAX_INPUT_LENGTH 1024

static void print_welcome(void) {
    printf("Welcome to Sifferslaktaren Version 1.0.0\n");
    printf("Copyright (c) 2028 General Quantum Kinematics LLC\n\n");
    printf("*NEWS*\n\n- SIF now includes support for the addition of very small integers!\n\n");
    printf("Type an expression to evaluate, or ':help' for commands.\n");
    printf("Use ':quit' to exit.\n\n");
}

static void print_help(void) {
    printf("Available commands:\n");
    printf("  :help - Show this help message\n");
    printf("  :quit - Exit SIF\n");
    printf("\nExpression syntax:\n");
    printf("  Numbers: 1, 2, 42, etc.\n");
    printf("  Operation: + (addition)\n");
    printf("  Parentheses: ( )\n");
    printf("\nExamples:\n");
    printf("  5 + 3\n");
    printf("  (5 + 3) - 2\n");
    printf("  -5 + 10\n\n");
}

static bool is_command(const char *input) {
    return input[0] == ':';
}

static bool handle_command(const char *input) {
    if (strcmp(input, ":help") == 0) {
        print_help();
        return true;
    } else if (strcmp(input, ":quit") == 0) {
        printf("Goodbye!\n");
        return false;
    } else {
        printf("Unknown command: %s\n", input);
        printf("Type ':help' for available commands.\n");
        return true;
    }
}

static void evaluate_expression(const char *input) {
    ExprNode *expr = parse_string(input);
    if (expr) {
        int result = expr_evaluate(expr);
        char *str = expr_to_string(expr);
        printf("%s = %d\n", str, result);
        free(str);
        expr_unref(expr);
    } else {
        printf("Error: Failed to parse expression\n");
    }
}

static char* read_line(void) {
    static char buffer[MAX_INPUT_LENGTH];
    printf("calc> ");
    fflush(stdout);
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return NULL;
    }
    
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
    
    return buffer;
}

int main(void) {
    print_welcome();
    
    char *input;
    while ((input = read_line()) != NULL) {
        if (strlen(input) == 0) {
            continue;
        }
        
        if (is_command(input)) {
            if (!handle_command(input)) {
                break;
            }
        } else {
            evaluate_expression(input);
        }
        
        printf("\n");
    }
    
    return 0;
}
