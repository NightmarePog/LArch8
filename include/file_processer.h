#ifndef FILE_PROCESSER
#define FILE_PROCESSER

#include <stdio.h>

void fp_read_file(FILE *file);

int fp_open_file(char *file_path, FILE **file_pointer);

#endif