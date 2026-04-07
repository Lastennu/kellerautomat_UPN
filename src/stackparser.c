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
        return -1;
    }
    int result = 0;
    int poppedelement;

    while((poppedelement = pop(stack)) != NUMBER_SPACER && poppedelement != -1) {
        result = result * BASE + poppedelement;
    }
    return result;
}