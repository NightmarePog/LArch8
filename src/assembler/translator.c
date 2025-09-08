// translator.c
//
// assembles the instructions into binary
//
// made by Lukáš Erl 4/9/2025

#include "a_compilation.h"
#include "a_types.h"
#include "types.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint64_t assemble_instruction(InstrBin *instr) {
  uint64_t assembled_instruction = 0;

  assembled_instruction |= ((uint64_t)instr->OP_CODE) << 48;
  assembled_instruction |= ((uint64_t)instr->ADDRESSING_MODE_0.uint16_t) << 32;
  assembled_instruction |= ((uint64_t)instr->ADDRESSING_MODE_1.uint16_t) << 16;
  assembled_instruction |= ((uint64_t)instr->ADDRESSING_MODE_2.uint16_t) << 0;

  printf("[ASSEMBLED LINE]: %016llX\n",
         (unsigned long long)assembled_instruction);
  return assembled_instruction;
}

uint64_t par_translate_line(char **tokenized_line) {
  InstrBin instruction;
  uint16_t token_buffer;
  for (int i = 0; i < MAX_TOKENS; i++) {
      printf("TOKEN BUFFER: %d\n", token_buffer);
    switch (i) {
    case OP_CODE: {
      bool found = false;
      for (int k = 0; instruction_set_dict[k].key != NULL; k++) {
        if (strcmp(instruction_set_dict[k].key, tokenized_line[i]) == 0) {
          found = true;
          token_buffer = instruction_set_dict[k].value;
          break;
        }
      }
      if (!found) {
        printf("Unknown opcode: %s\n", tokenized_line[i]);
      }
      break;
    }
    case ADDRESSING_MODE_0:
    case ADDRESSING_MODE_1:
    case ADDRESSING_MODE_2: {
      int size_token = strlen(tokenized_line[i]);
      char first_token = tokenized_line[i][0];
      char last_token = tokenized_line[i][size_token - 1];
      if (first_token == '[' || last_token == ']') {
        // Address
        printf("[TRANSLATION] [ADDRESS] %s - %X\n", tokenized_line[i],
               at_translate_address(tokenized_line[i]));
        token_buffer = at_translate_address(tokenized_line[i]);
      } else if (first_token == 'R') {
        // Register
        printf("[TRANSLATION] [REGISTER] %s - %X\n", tokenized_line[i],
               at_translate_register(tokenized_line[i]));
        token_buffer = at_translate_register(tokenized_line[i]);
      } else if (strtol(tokenized_line[i], NULL, 0)) {
        // imm
        printf("[TRANSLATION] [IMM] %s - %X\n", tokenized_line[i],
               at_translate_imm(tokenized_line[i]));
        token_buffer = at_translate_imm(tokenized_line[i]);
      }
    }
    }
    printf("[%d] - %hX\n", i, token_buffer);
    switch (i) {
    case OP_CODE:
      instruction.OP_CODE = token_buffer;
      break;
    case ADDRESSING_MODE_0:
      instruction.ADDRESSING_MODE_0.uint16_t = token_buffer;
      break;
    case ADDRESSING_MODE_1:
      instruction.ADDRESSING_MODE_1.uint16_t = token_buffer;
      break;
    case ADDRESSING_MODE_2:
      instruction.ADDRESSING_MODE_2.uint16_t = token_buffer;
      break;
    default:
      printf("undefined behavior\n - %d compiler.c", i);
    }
  }
  at_print_instruction(&instruction);
  return assemble_instruction(&instruction);
}
