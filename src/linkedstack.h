#ifndef LINKEDSTACK_H
#define LINKEDSTACK_H

#define $ -1

typedef struct StackNode {
    int value;
    struct StackNode *next;
} StackNode;

typedef struct {
    StackNode *top;
} LinkedStack;

void initialize(LinkedStack *stack);
int isEmpty(LinkedStack *stack);
int isFull(LinkedStack *stack);
void push(LinkedStack *stack, int value);
int pop(LinkedStack *stack);

void printStack(LinkedStack *stack);

#endif