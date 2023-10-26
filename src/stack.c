#include "stack.h"

void stack_init(vm_stack_t* stack) {
    stack->sp = 0;
    stack->error = SE_NONE;
    stack->size = STACK_SIZE;
}

void stack_term(vm_stack_t* stack) {
    stack->sp = 0;
}

void stack_push(vm_stack_t* stack, word value) {
    if (stack->error != SE_NONE) return;

    if (stack->sp >= STACK_SIZE) {
        stack->error = OVERFLOW;
        return;
    }

    stack->buffer[stack->sp] = value;
    stack->sp++;
}

word stack_pop(vm_stack_t* stack) {
    if (stack->error != SE_NONE) return 0;

    if (stack->sp == 0) {
        stack->error = UNDERFLOW;
        return 0;
    }

    stack->sp--;
    return stack_get(stack);
}

word stack_get(vm_stack_t* stack) {
    return stack->buffer[stack->sp];
}

void stack_set(vm_stack_t* stack, word value) {
    stack->buffer[stack->sp] = value;
}
