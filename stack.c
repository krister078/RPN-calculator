#include "stack.h"

void stack_init(Stack *stack) {
    stack->top = -1;
}

bool stack_is_empty(Stack *stack) {
    return stack->top == -1;
}

bool stack_is_full(Stack *stack) {
    return stack->top == MAX_STACK_SIZE - 1;
}

bool stack_push(Stack *stack, int value) {
    if (stack_is_full(stack)) {
        return false;
    }
    stack->data[++(stack->top)] = value;
    return true;
}

bool stack_pop(Stack *stack, int *value) {
    if (stack_is_empty(stack)) {
        return false;
    }
    *value = stack->data[(stack->top)--];
    return true;
}

bool stack_peek(Stack *stack, int *value) {
    if (stack_is_empty(stack)) {
        return false;
    }
    *value = stack->data[stack->top];
    return true;
}

int stack_size(Stack *stack) {
    return stack->top + 1;
}