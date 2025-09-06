// tokenization_and_parser
//
// a simple parser and syntax checker
//
// made by Lukáš Erl 4/9/2025

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TOKENS 4
#define MAX_LINE_LEN 256


// all register tokens
const char *reg_tokens[] = {"R1", "R2", "R3", "R4", NULL};


// checks if register exists
bool is_register(const char *token) {
  for (int i = 0; reg_tokens[i] != NULL; i++) {
    if (strcmp(token, reg_tokens[i]) == 0)
      return true;
  }
  return false;
}

/*
 checks if is number
 supports hex, dec, bin
*/
bool is_number(const char *s) {
  if (*s == '-' || *s == '+')
    s++;

  // hex numbers
  if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) {
    s += 2;
    if (*s == '\0')
      return 0;
    while (*s) {
      if (!isxdigit(*s))
        return false;
      s++;
    }
    return true;
  }

  // binary numbers
  if (s[0] == '0' && (s[1] == 'b' || s[1] == 'B')) {
    s += 2;
    if (*s == '\0')
      return 0;
    while (*s) {
      if (*s != '0' && *s != '1')
        return 0;
      s++;
    }
    return 1;
  }

  // decimal numbers
  if (*s == '\0')
    return 0;
  while (*s) {
    if (!isdigit(*s))
      return 0;
    s++;
  }
  return 1;
}

bool is_address(const char *token) {
  int token_size = strlen(token);
  if (token[0] == '[' && token[token_size - 1] == ']') {
    char *token_copy = malloc(token_size - 1);
    strncpy(token_copy, token + 1, token_size - 2);
    if (is_number(token_copy)) {
      return true;
    }
  }
  return false;
}

// decides if token is written as register token or number
bool is_adressing_mode(const char *token) {
  return is_register(token) || is_number(token) || is_address(token);
}
