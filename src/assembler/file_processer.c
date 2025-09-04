// file_processer.c
//
// this file have helper functions for file processing
//
// made by Lukáš Erl

#include <stdio.h>
#define MAX_LINE_SIZE 4

void read_file(FILE *file) {
  char line[MAX_LINE_SIZE];
  while (fgets(line, sizeof(line), file)) {
    printf("%s", line);
  }
}

int open_file(char *file_path, FILE **file_pointer) {
  FILE *file = fopen(file_path, "r");

  *file_pointer = file;
  return !file;
}