#ifndef GSM_STACK_H
#define GSM_STACK_H

#include "types.h"

#define STACK_SIZE 0x100

typedef enum stack_error {
    SE_NONE,
    OVERFLOW,
    UNDERFLOW
} stack_error;

typedef struct vm_stack_t {
    word buffer[STACK_SIZE];
    word size;
    word sp; // stack pointer
    stack_error error;
} vm_stack_t;

void stack_init(vm_stack_t* stack);
void stack_term(vm_stack_t* stack);

void stack_push(vm_stack_t* stack, word value);
word stack_pop(vm_stack_t* stack);

word stack_get(vm_stack_t* stack);
void stack_set(vm_stack_t* stack, word value);

#endif // GSM_STACK_H
