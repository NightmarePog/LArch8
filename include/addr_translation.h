#include "assembler_words.h"

int translate_register(char *string);
int translate_imm(char *string);
int translate_address(const char *string);
void print_instruction(INSTR_TRANS_STRUCT *instruction);