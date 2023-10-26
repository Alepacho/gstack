#ifndef GSM_RAM_H

#include "types.h"

typedef enum ram_error {
    RE_NONE,
    RE_ACCESS,
} ram_error;

typedef struct ram_t {
    word* buffer;
    word  size;
    ram_error error;
} ram_t;

void ram_init(ram_t* ram, word size);
void ram_term(ram_t* ram);

word ram_peek(ram_t* ram, word index);
void ram_poke(ram_t* ram, word index, word value);

#endif // GSM_RAM_H
