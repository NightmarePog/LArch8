// file_processer.c
//
// this file have helper functions for file processing
//
// made by Lukáš Erl

#include <stdint.h>
#include <stdio.h>
#define MAX_LINE_SIZE 4

void fp_read_file(FILE *file) {
  char line[MAX_LINE_SIZE];
  while (fgets(line, sizeof(line), file)) {
    printf("%s", line);
  }
}

int fp_open_file(char *file_path, FILE **file_pointer) {
  FILE *file = fopen(file_path, "r");

  *file_pointer = file;
  return !file;
}

void fp_output_program(const char *filename, const uint64_t *array, size_t length) {
    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        perror("Failed to open file");
        return;
    }

    size_t written = fwrite(array, sizeof(uint64_t), length, fp);
    if (written != length) {
        perror("fwrite failed");
    }

    fclose(fp);
}