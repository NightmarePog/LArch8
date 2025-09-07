#ifndef ASSEMBLER_WORDS
#define ASSEMBLER_WORDS

#include <stdint.h>

extern const int MAX_TOKENS;
extern const int MAX_LINES;
extern const int MAX_LINE_LEN;


typedef enum {
    OP_CODE,
    ADDRESSING_MODE_0,
    ADDRESSING_MODE_1, 
    ADDRESSING_MODE_2, 
} INSTR_ENUM;


typedef struct {
    int size;
    uint64_t* program;
} CompilationOutput; 

#endif
