#ifndef FILE_PROCESSER
#define FILE_PROCESSER

#include <stdio.h>

void read_file(FILE *file);

int open_file(char *file_path, FILE **file_pointer);

#endif