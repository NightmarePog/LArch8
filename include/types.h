#ifndef GLOBAL_TYPES
#define GLOBAL_TYPES

#include <stdint.h>
typedef struct {
    const char *key;
    int value;
} DictEntry;

typedef struct {
    uint16_t OP_CODE;
    uint16_t ADDRESSING_MODE_0;
    uint16_t ADDRESSING_MODE_1;
    uint16_t ADDRESSING_MODE_2;

} InstructionVal;

extern DictEntry const instruction_set_dict[];

#endif