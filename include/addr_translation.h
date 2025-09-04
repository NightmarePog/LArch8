#include "types.h"
#include <stdbool.h>

int at_translate_register(char *string);
int at_translate_imm(char *string);
int at_translate_address(const char *string);
void at_print_instruction(InstructionVal *instruction);
bool at_is_anumber(const char *string, int start_offset, int end_offset);