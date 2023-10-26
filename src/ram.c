#include "ram.h"

#include <stdlib.h>

void ram_init(ram_t* ram, word size) {
    ram->buffer = calloc(size, sizeof(word));
    ram->size = size;
    ram->error = RE_NONE;
}

void ram_term(ram_t* ram) {
    free(ram->buffer);
    ram->buffer = NULL;
}

word ram_peek(ram_t* ram, word index) {
    if (index >= ram->size) {
        ram->error = RE_ACCESS;
        return 0;
    }
    
    return ram->buffer[index];
}

void ram_poke(ram_t* ram, word index, word value) {
    if (index >= ram->size) {
        ram->error = RE_ACCESS;
        return;
    }

    ram->buffer[index] = value;
}
