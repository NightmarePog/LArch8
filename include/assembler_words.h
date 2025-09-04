#ifndef ASSEMBLER_WORDS
#define ASSEMBLER_WORDS
#include "assembler.h"
#include <stdint.h>
typedef enum {
    OP_CODE,
    ADDRESSING_MODE_0,
    ADDRESSING_MODE_1, 
    ADDRESSING_MODE_2, 
} INSTR_ENUM;

typedef struct {
    uint16_t OP_CODE;
    uint16_t ADDRESSING_MODE_0;
    uint16_t ADDRESSING_MODE_1;
    uint16_t ADDRESSING_MODE_2;

} INSTR_TRANS_STRUCT;

extern DictEntry instruction_set_dict[];
extern DictEntry register_set_dict[];

#endif