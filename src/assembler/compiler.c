// compiler.c
//
// core part of assembler
// compiles code into binary values
//
// made by Lukáš Erl 4/9/2025

#include "a_addr_translation.h"
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

  if (!at_is_anumber(string, 1, -1)) {
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
