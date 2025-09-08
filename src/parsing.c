// parser.c
//
// this is global parsing file used for both interpreter and assembler
//
// made by Lukáš Erl 4/9/2025

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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

char **par_str_to_lines(char *input) {
  int capacity = 4; // start up line length
  char **lines = malloc(capacity * sizeof(char *));
  int count = 0;

  while (*input != '\0') {
    // find line length
    int len = 0;
    char *start = input;
    while (input[len] != '\n' && input[len] != '\0') {
      len++;
    }

    char *line = malloc(len + 1);
    strncpy(line, start, len);
    line[len] = '\0';

    // if there are more lines than start up capacity, we allocate
    if (count >= capacity) {
      capacity *= 2;
      char **tmp = realloc(lines, capacity * sizeof(char *));
      if (!tmp) {
        // error handling
        for (int i = 0; i < count; i++)
          free(lines[i]);
        free(lines);
        return NULL;
      }
      lines = tmp;
    }

    lines[count++] = line;

    input += len;
    if (*input == '\n')
      input++; // skip new line
  }
  return lines;
}

