#ifndef ASSEMBLER
#define ASSEMBLER
#include <stdio.h>

// cuts of the comment
char* prec_remove_comments(char* line);
// gets whole line file input and tokenize it into lines
char** prec_tokenize_lines(char* input);
// tries to tokenize line, returns number of tokens and put tokens into char *tokens[]
int prec_tokenize_line(char *line, char *tokens[]);
// gets file and returns string
char* prec_get_string_from_file(FILE *file);
// tries to translate whole line into binary code
int prec_translate_line(char **tokenized_line);

#endif