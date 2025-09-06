#ifndef ASSEMBLER_WORDS
#define ASSEMBLER_WORDS

#include <stdint.h>

extern const int MAX_TOKENS;
extern const int MAX_LINES;
extern const int MAX_LINE_LEN;

typedef struct {
    const char *key;
    int value;
} DictEntry;

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

} InstructionVal;

typedef struct {
    int size;
    uint64_t* program;
} CompilationOutput; 

extern DictEntry instruction_set_dict[];
extern DictEntry register_set_dict[];

#endif
