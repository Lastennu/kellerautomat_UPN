#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include "linkedstack.h"

#define STATE_ZERO 0
#define STATE_ONE 1
#define STATE_TWO 2
#define INVALID_STATE -1
#define ACCEPTED_STATE STATE_ONE
#define RETURN_ACCEPTED 0
#define RETURN_DECLINED 1

int tempNumber;

int stateZero(LinkedStack *stack, char symbol) {
    if (pop(stack) == $) {
        if (symbol >= '0' && symbol <= '9') {
            push(stack, $);
            tempNumber = symbol - '0';
            return STATE_ONE;
        }
    }
    return INVALID_STATE;
}

int stateOne(LinkedStack *stack, char symbol) {
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

int stateTwo(LinkedStack *stack, char symbol) {
    int top = pop(stack);
    if (top == $) {
        push(stack, $);
        return STATE_ONE;
    }
    if (symbol == '+') {
        tempNumber += top;
        return STATE_TWO;
    } 
    if (symbol == '*') {
        tempNumber *= top;
        return STATE_TWO;
    }
    if (symbol >= '0' && symbol <= '9') {
        push(stack, top);
        push(stack, tempNumber);
        tempNumber = symbol - '0';
        return STATE_TWO;
    }
    return INVALID_STATE;
}

int kellerautomat(char stepMode, char *word) {
    LinkedStack stack;
    initialize(&stack);

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
            return RETURN_DECLINED;
        }
        if (currentState == INVALID_STATE) {
            printf("Verwerfend\n");
            return RETURN_DECLINED;
        }
       if (stepMode) {
           printStack(&stack);
           sleep(1);
       }
    }
    if (currentState == STATE_TWO) {
        currentState = stateTwo(&stack, '0');
    }
    if (currentState == ACCEPTED_STATE) {
        printf("Akzeptiert: %d\n", tempNumber);
        return RETURN_ACCEPTED;
    }
    printf("Verwerfend\n");
    return RETURN_DECLINED;
}

#ifndef KELLERAUTOMAT_NO_MAIN
int main() {
    char stepMode;

    printf("(S)tep-modus oder (l)auf-modus: ");
    scanf("%c", &stepMode);
    if (stepMode == 'l' || stepMode == 'L') {
        stepMode = 0;
    }

    char word[MAX_SIZE];
    printf("Wort (maximale Länge: %d): ", MAX_SIZE);
    scanf("%99s", word);
    return kellerautomat(stepMode, word);
}
#endif