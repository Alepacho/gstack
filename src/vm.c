#include "vm.h"

void vm_init(vm_t* vm, word msize) {
    vm->code    = NOTHING;
    vm->working = 1;
    vm->pc      = 0;
    vm->mar     = 0;
    vm->ir      = 0;

    stack_init(&vm->ds);
    stack_init(&vm->rs);

    ram_init(&vm->ram, msize);
}

void vm_term(vm_t* vm) {
    vm->working = 0;
    vm->pc = 0;
    stack_term(&vm->ds);
    stack_term(&vm->rs);
    ram_term(&vm->ram);
}

void vm_fetch(vm_t* vm) {
    vm->mar = vm->pc; // stores address of instruction
    vm->ir = vm->ram.buffer[vm->mar]; // stores instruction itself
    vm->pc = (vm->pc + 1) % vm->ram.size;
}

void vm_decode(vm_t* vm) {
    vm_stack_t* ds = &vm->ds;
    vm_stack_t* rs = &vm->rs;
    ram_t*     ram = &vm->ram;

    switch (vm->ir) {
        case BREAK: { vm->working = 0; } break;
        case STORE: {
            const word n1   = stack_pop(ds); 
            const word addr = stack_pop(ds); 
            ram_poke(ram, addr, n1);
        } break;
        case ADD: { 
            const word n1 = stack_pop(ds); 
            const word n2 = stack_pop(ds); 
            stack_push(ds, n1 + n2);
        } break;
        case SUB: { 
            const word n1 = stack_pop(ds); 
            const word n2 = stack_pop(ds); 
            stack_push(ds, n1 - n2);
        } break;
        case PUSH: { stack_push(rs, stack_pop(ds)); } break;
        case FETCH: { 
            const word addr = stack_pop(ds);
            stack_push(rs, ram_peek(ram, addr));
        } break;
        case AND: { 
            const word n1 = stack_pop(ds); 
            const word n2 = stack_pop(ds); 
            stack_push(ds, n1 && n2);
        } break;
        case DROP: { stack_pop(ds); } break;
        case DUP: { stack_push(ds, stack_get(ds)); } break;
        case OR: {
            const word n1 = stack_pop(ds); 
            const word n2 = stack_pop(ds); 
            stack_push(ds, n1 || n2);
        } break;
        case OVER: {
            const word n1 = stack_pop(ds); 
            const word n2 = stack_pop(ds); 
            stack_push(ds, n2); stack_push(ds, n1); stack_push(ds, n2);
        } break;
        case POP: { stack_push(ds, stack_pop(rs)); } break;
        case SWAP: {
            const word n1 = stack_pop(ds); 
            const word n2 = stack_pop(ds); 
            stack_push(ds, n1); stack_push(ds, n2);
        } break;
        case XOR: {
            const word n1 = stack_pop(ds); 
            const word n2 = stack_pop(ds); 
            stack_push(ds, !n1 != !n2);
        } break;
        case IF: {
            const word n1 = stack_pop(ds); 
            const word addr = ram_peek(ram, vm->pc);
            if (n1 == 0) {
                vm->pc = addr;
            } else vm->pc++;
        } break;
        case CALL: {
            stack_push(rs, vm->mar);
            vm->pc = ram_peek(ram, vm->pc);
        } break;
        case EXIT: {
            vm->pc = stack_pop(rs) + 2;
        } break;
        case LIT: {
            stack_push(ds, ram_peek(ram, vm->pc)); 
            vm->pc++; 
        } break;
        default: vm_error(vm, INSTRUCTION);
    }
}

void vm_execute(vm_t* vm) {
    vm_fetch(vm);
    vm_decode(vm);
    
    if (vm->ram.error != RE_NONE) vm_error(vm, MEMORY_BAD_ACCESS);
    if (vm->ds.error  != SE_NONE) vm_error(vm, vm->ds.error == OVERFLOW ? DATA_OVERFLOW : DATA_UNDERFLOW);
    if (vm->rs.error  != SE_NONE) vm_error(vm, vm->rs.error == OVERFLOW ? RETURN_OVERFLOW : RETURN_UNDERFLOW);
}

int vm_working(vm_t* vm) {
    return vm->working;
}

void vm_error(vm_t* vm, vm_error_code code) {
    if (vm->code != NOTHING) return;
    vm->code = code;
    vm->working = 0;
}

char* vm_error_str(vm_t* vm) {
    switch (vm->code) {
        case INSTRUCTION      : return "Illegal instruction";
        case DATA_OVERFLOW    : return "Data Stack Overflow";
        case DATA_UNDERFLOW   : return "Data Stack Underflow";
        case RETURN_OVERFLOW  : return "Return Stack Overflow";
        case RETURN_UNDERFLOW : return "Return Stack Underflow";
        case MEMORY_BAD_ACCESS: return "Memory Bad Access";
        default: return "Unknown";
    }
}
