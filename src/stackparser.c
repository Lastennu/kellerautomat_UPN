#include "stack.h"

void pushparse(Stack *stack, int value) {
    push(stack, NUMBER_SPACER);
    while(value > 0) {
        int valueToPush = value % BASE;
        value /= BASE;
        push(stack, valueToPush);
    }
}

int popparse(Stack *stack) {
    if (isEmpty(stack)) {
        return -1; // stack underflow
    }
    int result = 0;
    int poppedelement = 0;
    while(poppedelement = pop(stack) != NUMBER_SPACER) {
        result += poppedelement *= BASE;
    }
    return result;
}