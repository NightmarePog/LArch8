// precompiler.c
//
// gets input program ready for compilation process
//
// made by Lukáš Erl 4/9/2025

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"

// cuts off the comment
char *par_remove_comments(char *line) {
  char *comment_start = strchr(line, ';');
  if (comment_start != NULL) {
    *comment_start = '\0';
  }
  return line;
}

// gets file and returns string
char *par_get_string_from_file(FILE *file) {
  if (!file)
    return NULL;

  // get size of file
  fseek(file, 0, SEEK_END);
  long size = ftell(file);
  if (size < 0)
    return NULL; // ftell failed

  fseek(file, 0, SEEK_SET);

  char *buffer = malloc(size + 1);
  if (!buffer)
    return NULL;

  // this will load the file
  size_t read_size = fread(buffer, 1, size, file);
  buffer[read_size] = '\0'; // ends the string

  return buffer;
}

// tries to tokenize line, returns number of tokens and put tokens into char
// *tokens[]
int par_tokenize_line(char *line, char *tokens[MAX_TOKENS]) {
  int count = 0;
  char *token = strtok(line, " ");

  while (token != NULL && count < MAX_TOKENS) {
    tokens[count] = strdup(token); // allocate new memory for token
    if (!tokens[count]) {          // check malloc success
      // free previously allocated tokens before returning
      for (int j = 0; j < count; j++)
        free(tokens[j]);
      printf("memory allocation error");
      return true;
    }
    count++;
    token = strtok(NULL, " ");
  }
  return false;
}
