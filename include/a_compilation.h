#include "types.h"
#include <stdbool.h>

int at_translate_register(char *string);
int at_translate_imm(char *string);
int at_translate_address(const char *string);
void at_print_instruction(InstrBin *instruction);
bool at_is_anumber(const char *string, int start_offset, int end_offset);
// tries to translate whole line into binary code
uint64_t par_translate_line(char **tokenized_line);