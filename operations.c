#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "operations.h"

int op_add(Stack *stack) {
    int operand2, operand1;
    
    if (!stack_pop(stack, &operand2) || !stack_pop(stack, &operand1)) {
        return OP_FAILURE;
    }
    
    return stack_push(stack, operand1 + operand2) ? OP_SUCCESS : OP_FAILURE;
}

int op_subtract(Stack *stack) {
    int operand2, operand1;
    
    if (!stack_pop(stack, &operand2) || !stack_pop(stack, &operand1)) {
        return OP_FAILURE;
    }
    
    return stack_push(stack, operand1 - operand2) ? OP_SUCCESS : OP_FAILURE;
}

int op_multiply(Stack *stack) {
    int operand2, operand1;
    
    if (!stack_pop(stack, &operand2) || !stack_pop(stack, &operand1)) {
        return OP_FAILURE;
    }
    
    return stack_push(stack, operand1 * operand2) ? OP_SUCCESS : OP_FAILURE;
}

int op_divide(Stack *stack) {
    int operand2, operand1;
    
    if (!stack_pop(stack, &operand2) || !stack_pop(stack, &operand1)) {
        return OP_FAILURE;
    }
    
    if (operand2 == 0) {
        printf("Error: Division by zero\n");
        return OP_FAILURE;
    }
    
    return stack_push(stack, operand1 / operand2) ? OP_SUCCESS : OP_FAILURE;
}

int op_ln(Stack *stack) {
    int operand;
    
    if (!stack_pop(stack, &operand)) {
        return OP_FAILURE;
    }
    
    if (operand <= 0) {
        printf("Error: Logarithm of non-positive number\n");
        return OP_FAILURE;
    }
    
    return stack_push(stack, (int)log(operand)) ? OP_SUCCESS : OP_FAILURE;
}

int op_log(Stack *stack) {
    int base, operand;
    
    if (!stack_pop(stack, &base) || !stack_pop(stack, &operand)) {
        return OP_FAILURE;
    }
    
    if (operand <= 0 || base <= 0 || base == 1) {
        printf("Error: Invalid logarithm parameters\n");
        return OP_FAILURE;
    }
    
    return stack_push(stack, (int)(log(operand) / log(base))) ? OP_SUCCESS : OP_FAILURE;
}

int op_pi(Stack *stack) {
    return stack_push(stack, (int)PI) ? OP_SUCCESS : OP_FAILURE;
}

int op_e(Stack *stack) {
    return stack_push(stack, (int)E) ? OP_SUCCESS : OP_FAILURE;
}

int is_valid_operator(const char *token) {
    if (token[0] != '\0' && token[1] == '\0') {
        switch (token[0]) {
            case '+':
            case '-':
            case '*':
            case '/':
                return 1;
        }
    }
    
    return (strcmp(token, "ln") == 0 || 
            strcmp(token, "log") == 0 || 
            strcmp(token, "pi") == 0 || 
            strcmp(token, "e") == 0) ? 1 : 0;
}

int get_required_operands(const char *operator) {
    if (operator[0] != '\0' && operator[1] == '\0') {
        switch (operator[0]) {
            case '+':
            case '-':
            case '*':
            case '/':
                return 2;
        }
    }
    
    if (strcmp(operator, "log") == 0) {
        return 2;
    } else if (strcmp(operator, "ln") == 0) {
        return 1;
    } else if (strcmp(operator, "pi") == 0 || 
              strcmp(operator, "e") == 0) {
        return 0;
    }
    
    return -1; 
}

int execute_operation(Stack *stack, const char *operator) {
    if (operator[0] != '\0' && operator[1] == '\0') {
        switch (operator[0]) {
            case '+': return op_add(stack);
            case '-': return op_subtract(stack);
            case '*': return op_multiply(stack);
            case '/': return op_divide(stack);
        }
    }
    
    if (strcmp(operator, "ln") == 0) {
        return op_ln(stack);
    } else if (strcmp(operator, "log") == 0) {
        return op_log(stack);
    } else if (strcmp(operator, "pi") == 0) {
        return op_pi(stack);
    } else if (strcmp(operator, "e") == 0) {
        return op_e(stack);
    }
    
    return OP_FAILURE;
}
int validate_expression(char **tokens, int token_count, char **error_message) {
    if (token_count == 0) {
        *error_message = "Empty expression";
        return OP_FAILURE;
    }
    
    int operand_count = 0;
    
    for (int i = 0; i < token_count; i++) {
        char *token = tokens[i];
        char *endptr;
        long value = strtol(token, &endptr, 10);
        
        if (*endptr == '\0') {
            operand_count++;
        } else if (is_valid_operator(token)) {
            int required_operands = get_required_operands(token);
            
            if (operand_count < required_operands) {
                printf("Not enough operands for operator '%s' at token %d", token, i + 1);
                return OP_FAILURE;
            }
            
            operand_count = operand_count - required_operands + 1;
        } else {
            printf("Invalid token '%s' at position %d", token, i + 1);
            return OP_FAILURE;
        }
    }
    
    if (operand_count != 1) {
        printf("Expression should result in exactly one value, found %d", operand_count);
        return OP_FAILURE;
    }
    
    return OP_SUCCESS;
}