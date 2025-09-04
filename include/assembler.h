#ifndef ASSEMBLER
#define ASSEMBLER
#include <stdio.h>

// cuts of the comment
char* rem_comms_in_line(char* line);
// gets whole line file input and tokenize it into lines
char** tokenize_lines(char* input);
// tries to tokenize line, returns number of tokens and put tokens into char *tokens[]
int tokenize_line(char *line, char *tokens[]);
// gets file and returns string
char* get_string_from_file(FILE *file);
// tries to translate whole line into binary code
int translate_line(char **tokenized_line);

#endif