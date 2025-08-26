#include <stdio.h>
void read_file(FILE *file);
int open_file(char *file_path, FILE **file_pointer);
int translate_line(char **tokenized_line);