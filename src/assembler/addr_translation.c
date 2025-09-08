// addr_translation.c
//
// this file have functions to translate addresses into binary
// also having helper functip print_instruction
//
// made by Lukáš Erl
// this is not right probably

#include "types.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// debug stuff
void at_print_instruction(InstrBin *instruction) {
  printf("=========== INSTRUCTION ==============\n");
  printf("OP CODE: %hX\n", instruction->OP_CODE);
  printf("ADR MODE 1: %hX\n", instruction->ADDRESSING_MODE_0.uint16_t);
  printf("ADR MODE 2: %hX\n", instruction->ADDRESSING_MODE_1.uint16_t);
  printf("ADR MODE 3: %hX\n", instruction->ADDRESSING_MODE_2.uint16_t);
  printf("=========== INSTRUCTION END===========\n");
}

bool at_is_anumber(const char *string, int start_offset, int end_offset) {
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

uint16_t at_translate_register(char *string) {
  int address_prefix = REGIS;
  if (string[0] != 'R')
    return 0;

  switch (string[1]) {
  case '1':
    return (address_prefix << 8) | 1;
  case '2':
    return (address_prefix << 8) | 2;
  case '3':
    return (address_prefix << 8) | 3;
  case '4':
    return (address_prefix << 8) | 4;
  default:
    fprintf(stderr, "error, unable to compile '%s'", string);
    return 0;
  }
}

int parse_number(const char *s) {
  if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) {
    // hex
    return strtoull(s, NULL, 16);
  } else if (s[0] == '0' && (s[1] == 'b' || s[1] == 'B')) {
    // binary
    int val = 0;
    s += 2;
    while (*s == '0' || *s == '1') {
      val = (val << 1) | (*s - '0');
      s++;
    }
    return val;
  } else {
    // decimal
    return strtoull(s, NULL, 10);
  }
}

int at_translate_imm(char *string) { return (IMM << 8) | parse_number(string); }

// returns 0 if failed
// else returns number as address
uint16_t at_translate_address(const char *string) {
  int address_prefix = ADDRESS;

  // validates if it's even a number
  if (!at_is_anumber(string, 1, -1)) {
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
  return ((uint16_t)address_prefix << 8) | val;
}
