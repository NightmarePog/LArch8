// addr_translation.c
//
// this file have functions to translate addresses into binary
// also having helper functip print_instruction
//
// made by Lukáš Erl
// this is not right probably
#ifndef ADDR_TRANSLATION
#define ADDR_TRANSLATION

#include "types.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// debug stuff
void print_instruction(InstructionVal *instruction) {
  printf("=========== INSTRUCTION ==============\n");
  printf("OP CODE: %hX\n", instruction->OP_CODE);
  printf("ADR MODE 1: %hX\n", instruction->ADDRESSING_MODE_0);
  printf("ADR MODE 2: %hX\n", instruction->ADDRESSING_MODE_1);
  printf("ADR MODE 3: %hX\n", instruction->ADDRESSING_MODE_2);
  printf("=========== INSTRUCTION END===========\n");
}

bool is_anumber(const char *string, int start_offset, int end_offset) {
  int len = strlen(string);
  if (start_offset < 0 || end_offset > len) {
    printf("offset bigger than string size\n");
    return false;
  }

  for (int i = start_offset; i < end_offset; i++) {
    if (!isdigit((unsigned char)string[i])) {
      printf("%d is not a digit\n", string[i]);
      return false;
    }
  }
  return true;
}

int translate_register(char *string) {
  int address_prefix = 2;
  if (string[0] != 'R')
    return 0;
  switch (string[1]) {
  case '1':
    return (1 << address_prefix) | 2;
  case '2':
    return (2 << address_prefix) | 2;
  case '3':
    return (3 << address_prefix) | 2;
  case '4':
    return (4 << address_prefix) | 2;
  }
}

int translate_imm(char *string) { return string - string + 1; }

// returns 0 if failed
// else returns number as address
int translate_address(const char *string) {
  int address_prefix = 3;

  // validates if it's even a number
  if (!is_anumber(string, 1, -1)) {
    fprintf(stderr, "syntax error, %s is not a number in brackets\n", string);
    return 0;
  }

  size_t len = strlen(string);

  // cutting of [ and ]
  char string_copy[5];
  if (len - 2 >= sizeof(string_copy)) {
    fprintf(stderr, "number too long\n");
    return 0;
  }

  strncpy(string_copy, string + 1, len - 2);
  string_copy[len - 2] = '\0';

  // translating from string to long
  char *endptr;
  long val = strtol(string_copy, &endptr, 0);

  // checking if success
  if (*endptr != '\0') {
    printf("syntax error, %s is not a valid number\n", string);
    return 0;
  }

  // controlling if value is between 0 and 255
  if (val < 0 || val > 255) {
    printf("value out of range (0-255): %s\n", string);
    return 0;
  }
  printf("[INTERNAL] - VAL: %ld, PREFIX: %d", val, address_prefix);
  return ((int)val << address_prefix) | 2;
}

#endif