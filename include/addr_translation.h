#include "types.h"
#include <stdbool.h>

int translate_register(char *string);
int translate_imm(char *string);
int translate_address(const char *string);
void print_instruction(InstructionVal *instruction);
bool is_anumber(const char *string, int start_offset, int end_offset);