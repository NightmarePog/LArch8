#include "addr_translation.h"
#include "assembler.h"
#include "types.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_SIZE 128
#define MAX_TOKENS 4

// returns 0 if failed
// else returns number as address
int translate_address(const char *string) {
  int address_prefix = 3;

  if (!is_anumber(string, 1, -1)) {
    fprintf(stderr, "syntax error, %s is not a number in brackets\n", string);
    return 0;
  }

  size_t len = strlen(string);

  // cutting of [ and ]
  char string_copy[5];
  if (len - 2 >= sizeof(string_copy)) {
    fprintf(stderr, "invalid number, expected 0-255, got %s\n", string_copy);
    return 0;
  }

  strncpy(string_copy, string + 1, len - 2);
  string_copy[len - 2] = '\0';

  // translating from string to long
  char *endptr;
  long val = strtol(string_copy, &endptr, 0);

  // checking if success
  if (*endptr != '\0') {
    fprintf(stderr, "syntax error, %s is not a valid number\n", string);
    return 0;
  }

  // controlling if value is between 0 and 255
  if (val < 0 || val > 255) {
    fprintf(stderr, "value out of range (0-255): %s\n", string);
    return 0;
  }
  return ((int)val << address_prefix) | 2;
}

// gets tokenized line and translates it to the binary
int translate_line(char **tokenized_line) {
  InstructionVal instruction;
  uint16_t token_buffer;

  for (int i = 0; i < MAX_TOKENS; i++) {
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
        fprintf(stderr, "Unknown opcode: %s\n", tokenized_line[i]);
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
               translate_address(tokenized_line[i]));
        token_buffer = translate_address(tokenized_line[i]);
      } else if (first_token == 'R') {
        // Register
        printf("[TRANSLATION] [REGISTER] %s - %X\n", tokenized_line[i],
               translate_register(tokenized_line[i]));
        token_buffer = translate_register(tokenized_line[i]);
      } else if (strtol(tokenized_line[i], NULL, 0)) {
        // imm
        printf("[TRANSLATION] [IMM] %s - %X\n", tokenized_line[i],
               translate_imm(tokenized_line[i]));
        token_buffer = translate_imm(tokenized_line[i]);
      }
    }
    }
    printf("[%d] - %hX\n", i, token_buffer);

    switch (i) {
    case OP_CODE:
      instruction.OP_CODE = token_buffer;
      break;
    case ADDRESSING_MODE_0:
      instruction.ADDRESSING_MODE_0 = token_buffer;
      break;
    case ADDRESSING_MODE_1:
      instruction.ADDRESSING_MODE_1 = token_buffer;
      break;
    case ADDRESSING_MODE_2:
      instruction.ADDRESSING_MODE_2 = token_buffer;
      break;
    default:
      fprintf(stderr,
              "Error, while translating line, expected int 0 to 3, got %d", i);
    }
  }
  print_instruction(&instruction);
  return 0;
}
