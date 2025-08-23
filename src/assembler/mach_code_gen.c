#include <string.h>
#include "structs.h"

// instructions and their OP codes
const DictEntry dict_instr[] = {
    { "NULL", 0x00 },
    { "ADD",  0x01 },
    { "SUB",  0x02 },
    { "OR",   0x03 },
    { "NOT",  0x04 },
    { "AND",  0x05 },
    { "MUL",  0x06 },
    { "DIV",  0x07 },
    { "JE",   0x08 },
    { "JG",   0x09 },
    { "JL",   0x0A },
    { "JMP",  0x0B },
    { NULL,    0   }
};

// registers and their address
const DictEntry dict_reg[] = {
    {"R0", 0x00},
    {"R1", 0x01},
    {"R2", 0x02},
    {"R3", 0x03},
    {"R4", 0x04},

};

// looks up for op code
int lookup_opcode(const char *key) {
    for (int i = 0; dict_instr[i].key != NULL; i++) {
        if (strcmp(dict_instr[i].key, key) == 0) {
            return dict_instr[i].value;
        }
    }
    return -1; // didn't found
}
