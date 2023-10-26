#ifndef GSM_VM_H
#define GSM_VM_H

#include "types.h"
#include "stack.h"
#include "ram.h"

typedef enum vm_opcode {
    //        m : data stack              : return stack : from -> to
    BREAK, // 0 : (         --          ) : (    --    ) : ? -> ?
    STORE, // 0 : ( n1 addr --          ) : (    --    ) : d -> p
    ADD,   // 0 : ( n1 n2   -- n3       ) : (    --    ) : d -> d
    SUB,   // 0 : ( n1 n2   -- n3       ) : (    --    ) : d -> d
    PUSH,  // 0 : ( n1      --          ) : (    -- n1 ) : d -> r
    FETCH, // 0 : ( addr    -- n1       ) : (    --    ) : d -> d
    AND,   // 0 : ( n1 n2   -- n3       ) : (    --    ) : d -> d
    DROP,  // 0 : ( n1      --          ) : (    --    ) : d -> d
    DUP,   // 0 : ( n1      -- n1 n1    ) : (    --    ) : d -> d
    OR,    // 0 : ( n1 n2   -- n3       ) : (    --    ) : d -> d
    OVER,  // 0 : ( n1 n2   -- n1 n2 n1 ) : (    --    ) : d -> d
    POP,   // 0 : (         -- n1       ) : ( n1 --    ) : r -> d
    SWAP,  // 0 : ( n1 n2   -- n2 n1    ) : (    --    ) : d -> d
    XOR,   // 0 : ( n1 n2   -- n3       ) : (    --    ) : d -> d
    IF,    // 1 : ( n1      --          ) : (    --    ) : d -> ?
    CALL,  // 1 : (         --          ) : (    -- pc ) : ? -> ?
    EXIT,  // 0 : (         --          ) : ( pc --    ) : ? -> ?
    LIT,   // 1 : (         -- n1       ) : (    --    ) : ? -> d
} vm_opcode;

typedef enum vm_error_code {
    NOTHING,
    INSTRUCTION,
    DATA_OVERFLOW,
    DATA_UNDERFLOW,
    RETURN_OVERFLOW,
    RETURN_UNDERFLOW,
    MEMORY_BAD_ACCESS
} vm_error_code;

typedef struct vm_t {
    // program, memory-address and instruction registers
    word pc, mar, ir;
    vm_stack_t ds, rs; // data and return stacks
    ram_t ram;
    int working;
    vm_error_code code;
} vm_t;

void vm_init(vm_t* vm, word msize);
void vm_term(vm_t* vm);

void vm_fetch(vm_t* vm);
void vm_decode(vm_t* vm);
void vm_execute(vm_t* vm);

int vm_working(vm_t* vm);
void vm_error(vm_t* vm, vm_error_code code);
char* vm_error_str(vm_t* vm);

#endif // GSM_VM_H
