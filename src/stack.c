#include "stack.h"

void initialize(Stack *stack) {
    stack->top = $;
}

int isEmpty(Stack *stack) {
    return stack->top == $;
}

int isFull(Stack *stack) {
    return stack->top == MAX_SIZE - 1;
}

void push(Stack *stack, int value) {
    if (isFull(stack)) {
        return; // stack overflow
    }
    stack->arr[++stack->top] = value;
}

int pop(Stack *stack) {
    if (isEmpty(stack)) {
        return -1; // stack underflow
    }
    return stack->arr[stack->top--];
}
