#include <stdlib.h>
#include <stdio.h>

#include "vm.h"

int main(void) {
    printf("%s\n", "A Generic Stack Machine!");

    vm_t vm;
    vm_init(&vm, 1024); // in 'word' size
    
    vm.ram.buffer[0] = LIT;
    vm.ram.buffer[1] = 1280; // n1
    vm.ram.buffer[2] = LIT;
    vm.ram.buffer[3] = 1; // addr
    vm.ram.buffer[4] = ADD;
    vm.ram.buffer[5] = CALL;
    vm.ram.buffer[6] = 100;
    vm.ram.buffer[7] = BREAK;
    vm.ram.buffer[100] = LIT;
    vm.ram.buffer[101] = 1;
    vm.ram.buffer[102] = ADD;
    vm.ram.buffer[103] = EXIT;
        
    while (vm_working(&vm)) {
        vm_execute(&vm);
    }

    if (vm.code != NOTHING) {
        printf("Program exception: %s\n", vm_error_str(&vm));
    }

    vm_term(&vm);
    return 0;
}
