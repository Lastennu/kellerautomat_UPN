#include "stack.h"



void initialize(Stack *stack) {
    stack->top = TOP;
}

int isEmpty(Stack *stack) {
    return stack->top == TOP;
}

int isFull(Stack *stack) {
    return 0;
}

void push(Stack *stack, int value) {
    stack->arr[0] = stack->arr[0] * BASE + value;
}

int pop(Stack *stack) {
    if (isEmpty(stack)) {
        return -1; // stack underflow
    }
    int symbol = stack->arr[0] / BASE;
    stack->arr[0] = stack->arr[0] % BASE;
    return symbol;
}