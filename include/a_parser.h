#ifndef ASSEMBLER
#define ASSEMBLER
#include <stdint.h>

// cuts of the comment
char* par_remove_comments(char* line);
// tries to tokenize line, returns number of tokens and put tokens into char *tokens[]
int par_tokenize_line(char *line, char *tokens[]);


#endif