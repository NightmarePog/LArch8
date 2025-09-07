// parser.c
//
// this is global parsing file used for both interpreter and assembler
//
// made by Lukáš Erl 4/9/2025

#include <stdio.h>
#include <stdlib.h>

// gets file and returns string
char *prec_get_string_from_file(FILE *file) {
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