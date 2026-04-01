#ifndef STACK_H
#define STACK_H

#define MAX_SIZE 100

#define $ -1

typedef struct {
    int arr[MAX_SIZE];
    int top;
} Stack;

void initialize(Stack *stack);
int isEmpty(Stack *stack);
int isFull(Stack *stack);
void push(Stack *stack, int value);
int pop(Stack *stack);

#endif
