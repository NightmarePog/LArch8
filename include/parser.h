#ifndef GLOBAL_PARSER
#define GLOBAL_PARSER

#include <stdio.h>


// gets file and returns string
char* par_get_string_from_file(FILE *file);
// gets string and distributes into lines
char** par_str_to_lines(char* input);

#endif