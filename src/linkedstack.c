#include <stdio.h>
#include <stdlib.h>
#include "linkedstack.h"

void initialize(LinkedStack *stack) {
    stack->top = NULL;
}

int isEmpty(LinkedStack *stack) {
    return stack->top == NULL;
}

int isFull(LinkedStack *stack) {
    return 0;
}

void push(LinkedStack *stack, int value) {
    StackNode *newNode = (StackNode *)malloc(sizeof(StackNode));
    if (newNode == NULL) {
        printf("Stack overflow: memory allocation failed\n");
        return;
    }

    newNode->value = value;
    newNode->next = stack->top;

    stack->top = newNode;
}

int pop(LinkedStack *stack) {
    if (isEmpty(stack)) {
        return $;
    }

    StackNode *temp = stack->top;
    int poppedValue = temp->value;

    stack->top = temp->next;

    free(temp);

    return poppedValue;
}

void printRecursive(StackNode *node) {
    if (node == NULL) {
        return;
    }
    printRecursive(node->next);
    printf("%d, ", node->value);
}

void printStack(LinkedStack *stack) {
    printf("Current stack: ");
    printRecursive(stack->top);
    printf("\n");
}