#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "stack.h"
#include "operations.h"

#define MAX_INPUT_SIZE 1000
#define MAX_TOKEN_SIZE 50

void free_tokens(char** tokens, int count);

char** tokenize_expression(const char* expression, int* token_count) {
    int count = 0;
    bool in_token = false;
    
    for (int i = 0; expression[i] != '\0'; i++) {
        if (!isspace(expression[i])) {
            if (!in_token) {
                count++;
                in_token = true;
            }
        } else {
            in_token = false;
        }
    }
    
    char** tokens = (char**)malloc(count * sizeof(char*));
    if (tokens == NULL) {
        return NULL;
    }
    
    *token_count = 0;
    in_token = false;
    int token_start = 0;
    
    for (int i = 0; expression[i] != '\0'; i++) {
        if (!isspace(expression[i])) {
            if (!in_token) {
                token_start = i;
                in_token = true;
            }
        } else {
            if (in_token) {
                int token_length = i - token_start;
                tokens[*token_count] = (char*)malloc((token_length + 1) * sizeof(char));
                if (tokens[*token_count] == NULL) {
                    free_tokens(tokens, *token_count);
                    return NULL;
                }
                
                strncpy(tokens[*token_count], expression + token_start, token_length);
                tokens[*token_count][token_length] = '\0';
                (*token_count)++;
                in_token = false;
            }
        }
    }
    
    if (in_token) {
        int token_length = strlen(expression) - token_start;
        tokens[*token_count] = (char*)malloc((token_length + 1) * sizeof(char));
        if (tokens[*token_count] == NULL) {
            free_tokens(tokens, *token_count);
            return NULL;
        }
        
        strncpy(tokens[*token_count], expression + token_start, token_length);
        tokens[*token_count][token_length] = '\0';
        (*token_count)++;
    }
    
    return tokens;
}

void free_tokens(char** tokens, int count) {
    if (tokens == NULL) {
        return;
    }
    
    for (int i = 0; i < count; i++) {
        free(tokens[i]);
    }
    
    free(tokens);
}

int main() {
    char input[MAX_INPUT_SIZE];
    Stack operands;
    
    stack_init(&operands);
    
    printf("Enter expression: ");
    
    if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL) {
        printf("Error.\n");
        return 1;
    }
    
    size_t len = strlen(input);
    if (len > 0 && input[len-1] == '\n') {
        input[len-1] = '\0';
    }
    
    int token_count = 0;
    char** tokens = tokenize_expression(input, &token_count);
    
    if (tokens == NULL) {
        printf("Error tokenizing.\n");
        return 1;
    }
    
    char* error_message = NULL;
    if (validate_expression(tokens, token_count, &error_message) == OP_FAILURE) {
        if (error_message != NULL) {
            printf("Error: %s\n", error_message);
        } else {
            printf("Invalid expression\n");
        }
        free_tokens(tokens, token_count);
        return 1;
    }
    
    for (int i = 0; i < token_count; i++) {
        char* endptr;
        int value = (int)strtol(tokens[i], &endptr, 10);
        
        if (*endptr == '\0') {
            if (!stack_push(&operands, value)) {
                printf("Error: Stack overflow\n");
                free_tokens(tokens, token_count);
                return 1;
            }
            printf("Pushed: %d\n", value);
        } else {
            printf("Found operator: %s\n", tokens[i]);
            
            if (is_valid_operator(tokens[i])) {
                int result = execute_operation(&operands, tokens[i]);
                
                if (result == OP_SUCCESS) {
                    int top_value;
                    if (stack_peek(&operands, &top_value)) {
                        printf("Operation result: %d\n", top_value);
                    }
                } else {
                    printf("Operation failed\n");
                }
            } else {
                printf("Error: Unknown operator '%s'\n", tokens[i]);
            }
        }
    }
    
    if (!stack_is_empty(&operands)) {
        int result;
        stack_pop(&operands, &result);
        printf("\nFinal result: %d\n", result);
        
    } else {
        printf("\nNo result\n");
    }
    
    free_tokens(tokens, token_count);
    
    return 0;
}

