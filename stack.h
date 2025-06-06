#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

#define MAX_STACK_SIZE 100

typedef struct {
    int data[MAX_STACK_SIZE];
    int top;
} Stack;

void stack_init(Stack *stack);
bool stack_is_empty(Stack *stack);
bool stack_is_full(Stack *stack);
bool stack_push(Stack *stack, int value);
bool stack_pop(Stack *stack, int *value);
bool stack_peek(Stack *stack, int *value);
int stack_size(Stack *stack);

#endif