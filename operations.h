#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <math.h>
#include "stack.h"

#define PI 3.14159265358979323846
#define E 2.71828182845904523536

#define OP_SUCCESS 1
#define OP_FAILURE 0

int op_add(Stack *stack);
int op_subtract(Stack *stack);
int op_multiply(Stack *stack);
int op_divide(Stack *stack);
int op_ln(Stack *stack);
int op_log(Stack *stack);
int op_pi(Stack *stack);
int op_e(Stack *stack);

int validate_expression(char **tokens, int token_count, char **error_message);

int is_valid_operator(const char *token);

int get_required_operands(const char *op);

int execute_operation(Stack *stack, const char *op);

#endif