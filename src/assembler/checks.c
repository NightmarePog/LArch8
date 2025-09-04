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

// all instructions tokens
const char *instr_tokens[] = {"NULL", "ADD", "SUB", "OR", "NOT", "AND", "MUL",
                              "DIV",  "JE",  "JG",  "JL", "JMP", "HLT", NULL};

// all register tokens
const char *reg_tokens[] = {"R1", "R2", "R3", "R4", NULL};

// checks if instruction exists
bool is_valid_instruction(const char *token) {
  for (int i = 0; instr_tokens[i] != NULL; i++) {
    if (strcmp(token, instr_tokens[i]) == 0)
      return true;
  }
  return false;
}

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

// tries to tokenize line, returns number of tokens and put tokens into char
// *tokens[]
int prec_tokenize_line(char *line, char *tokens[MAX_TOKENS]) {
  int count = 0;
  char *token = strtok(line, " ");

  while (token != NULL && count < MAX_TOKENS) {
    tokens[count] = strdup(token); // allocate new memory for token
    if (!tokens[count]) {          // check malloc success
      // free previously allocated tokens before returning
      for (int j = 0; j < count; j++)
        free(tokens[j]);
      printf("memory allocation error");
      return true; // memory allocation error
    }
    count++;
    token = strtok(NULL, " ");
  }

  if (token != NULL) {
    printf("token is null\n");
    return true;
  } 
  // more tokens than MAX_TOKENS
  if (count != MAX_TOKENS) {
    printf("not enough parameters\n");
    return true;
  }
  if (!is_valid_instruction(tokens[0])) {
    printf("Error, %s is not a valid instruction!", tokens[0]);
    return true;
  }

  for (int i = 1; i < count; i++) {
    if (!is_adressing_mode(tokens[i]))
      return true;
  }

  return false;
}
