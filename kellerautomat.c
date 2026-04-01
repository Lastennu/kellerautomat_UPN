#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "stack.h"

#define STATE_ZERO 0
#define STATE_ONE 1
#define STATE_TWO 2
#define INVALID_STATE -1
#define ACCEPTED_STATE STATE_ONE

int tempNumber;

int stateZero(Stack *stack, char symbol) {
    if (pop(stack) == $) {
        if (symbol >= '0' && symbol <= '9') {
            push(stack, $);
            tempNumber = symbol - '0';
            return STATE_ONE;
        }
        return INVALID_STATE;
    }
    return INVALID_STATE;
}

int stateOne(Stack *stack, char symbol) {
    if (pop(stack) == $) {
        if (symbol >= '0' && symbol <= '9') {
            push(stack, $);
            push(stack, tempNumber);
            tempNumber = symbol - '0';
            return STATE_TWO;
        }
    }
    return INVALID_STATE;
}

int stateTwo(Stack *stack, char symbol) {
    int top = pop(stack);
    if (top == $) {
        push(stack, $);
        return STATE_ONE;
    }
    if (symbol == '+' || symbol == '*') {
        if (symbol == '+') {
            tempNumber += top;
            return STATE_TWO;
        } else {
            tempNumber *= top;
            return STATE_TWO;
        }
    }
    if (symbol >= '0' && symbol <= '9') {
        if (top != $) {
            push(stack, top);
            push(stack, tempNumber);
            tempNumber = symbol - '0';
            return STATE_TWO;
        }
    }
    return INVALID_STATE;
}

int main() {
    Stack stack;
    initialize(&stack);
    char stepMode;

    printf("(S)tep-modus oder (l)auf-modus: ");
    scanf("%c", &stepMode);
    if (stepMode == 'l') {
        stepMode = 0;
    }

    char word[MAX_SIZE];
    printf("Wort (maximale Länge: %d): ", MAX_SIZE);
    scanf("%99s", word);

    int currentState = STATE_ZERO;

    for (int i = 0; word[i] != '\0'; i++) {
        switch (currentState)
        {
        case STATE_ZERO:
            currentState = stateZero(&stack, word[i]);
            break;
        case STATE_ONE:
            currentState = stateOne(&stack, word[i]);
            break;
        case STATE_TWO:
            currentState = stateTwo(&stack, word[i]);
            if (currentState == STATE_ONE) {
                i--;
            }
            break;
        default:
            printf("Invalid state\n");
            return 1;
        }
        if (currentState == INVALID_STATE) {
            printf("Verwerfend\n");
            return 1;
        }
        if (stepMode) {
            printf("Current stack: ");
            for (int i = 0; i < stack.top; i++) {
                printf("%d, ", stack.arr[i]);
            }
            printf("\n");
            sleep(1);
        }
    }
    printf("Akzeptiert: %d\n", tempNumber);
    return 0;
}
/*
int main() {
    Stack stack;
    initialize(&stack);
    char stepMode;

    printf("(S)tep-modus oder (l)auf-modus: ");
    scanf("%c", &stepMode);
    if (stepMode == 'l') {
        stepMode = 0;
    }

    char word[MAX_SIZE];
    printf("Wort (maximale Länge: %d): ", MAX_SIZE);
    scanf("%s", word);

    for (int i = 0; i < sizeof(word); i++) {
        if (stepMode) {
            printf("Current stack: ");
            for (int i = 0; i < stack.top; i++) {
                printf("%d, ", stack.arr[i]);
            }
            printf("\n");
            sleep(1);
        }
        char symbol = word[i];
        if (symbol == '\0') {
            break;
        }
        int top = pop(&stack);
        if (top != -1 && (symbol == '+' || symbol == '*')) {
            int nextTop = pop(&stack);
            if (nextTop != -1) {
                if (symbol == '+') {
                    push(&stack, top + nextTop);
                    continue;
                } else {
                    push(&stack, top * nextTop);
                    continue;
                }
            }
        } else {
            int number = symbol - '0';
            if (top == -1) {
                push(&stack, number);
                continue;
            } else {
                push(&stack, top);
                push(&stack, number);
                continue;
            }
        }
        printf("Verwerfend\n");
        return 1;
    }

    int result = pop(&stack);
    int empty = pop(&stack);
    if (empty == -1) {
        printf("Akzeptiert: %d\n", result);
        return 0;
    }
    printf("Verwerfend\n");
    return 1;
}
    */