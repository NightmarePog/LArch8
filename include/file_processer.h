#ifndef FILE_PROCESSER
#define FILE_PROCESSER

#include <stdint.h>
#include <stdio.h>

void fp_read_file(FILE *file);

int fp_open_file(char *file_path, FILE **file_pointer);

void fp_output_program(const char *filename, const uint64_t *array, size_t length);


#endif