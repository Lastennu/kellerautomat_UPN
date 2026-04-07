#include "stack.h"

#define BASE 12
#define NUMBER_SPACER 11
#define TOP 12

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
    stack->arr[1] = stack->arr[1] * BASE + value;
}

int pop(Stack *stack) {
    if (isEmpty(stack)) {
        return -1; // stack underflow
    }
    int symbol = stack->arr[1] / BASE;
    stack->arr[1] = arr[1] % BASE;
    return symbol;
}