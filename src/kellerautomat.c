#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include "stackparser.h"

#define STATE_ZERO 0
#define STATE_ONE 1
#define STATE_TWO 2
#define INVALID_STATE -1
#define ACCEPTED_STATE STATE_ONE
#define RETURN_ACCEPTED 0
#define RETURN_DECLINED 1

int tempNumber;

int stateZero(Stack *stack, char symbol) {
    if (popparse(stack) == $) {
        if (symbol >= '0' && symbol <= '9') {
            pushparse(stack, $);
            tempNumber = symbol - '0';
            return STATE_ONE;
        }
    }
    return INVALID_STATE;
}

int stateOne(Stack *stack, char symbol) {
    if (popparse(stack) == $) {
        if (symbol >= '0' && symbol <= '9') {
            pushparse(stack, $);
            pushparse(stack, tempNumber);
            tempNumber = symbol - '0';
            return STATE_TWO;
        }
    }
    return INVALID_STATE;
}

int stateTwo(Stack *stack, char symbol) {
    int top = popparse(stack);
    if (top == $) {
        pushparse(stack, $);
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
        pushparse(stack, top);
        pushparse(stack, tempNumber);
        tempNumber = symbol - '0';
        return STATE_TWO;
    }
    return INVALID_STATE;
}

int kellerautomat(char stepMode, char *word) {
    Stack stack;
    initialize(&stack);
    pushparse(&stack, $);

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
            printf("Current stack: ");
            for (int i = 0; i <= stack.top; i++) {
                printf("%d, ", stack.arr[i]);
            }
            printf("\n");
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