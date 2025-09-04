
// MAIN.C
//
// this is entry point of whole program
// it gets arguments proceeds them and later gives output
// made by Lukáš Erl 4/9/2025 

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "assembler.h"
#include "file_processer.h"
#include "addr_translation.h"

#define MAX_LINE_SIZE 128
#define MAX_TOKENS 4


// debug stuff

void print_tokens(char **program_tokens) {
    if (!program_tokens) return;

    for (int i = 0; i != (MAX_TOKENS); i++) {
        printf("%s\n", program_tokens[i]);
    }
    printf("===END OF THE LINE===\n");
}

// divides program into lines, every line into token and after that it gets translated into binary
int assemble_program(char **program_pointer) {
    if (!program_pointer) return 1;
    char *copy;
    char *tokens[MAX_TOKENS];
    for (int i = 0; program_pointer[i] != NULL; i++) {
        copy = strdup(program_pointer[i]);
        program_pointer[i] = rem_comms_in_line(copy); // removing comments
        if (tokenize_line(program_pointer[i], tokens) == 0) {
            translate_line(tokens);
            print_tokens(tokens);
        } else {
            printf("tokenization failed\n");
            return 1;
        }
    }
    free(copy);

    return 0;
}


// proceeds the path argument, loads file and tries to assemble it
int init(char *file_path) {
    FILE *file = NULL;
    if (open_file(file_path, &file) == 0) {
        char *program_text = get_string_from_file(file);
        char **program_lines = tokenize_lines(program_text);
        assemble_program(program_lines);
    } else {
        printf("failed to open file\n");
        return 1;
    }
    fclose(file);
    return 0;
}

int main(int argc, char *argv[]) {
    // controls if path argument exists
    if (argc >= 2) {
        if(init(argv[1]) != 0) {
            printf("failed to compile\n");
            return 1;
        }
    } else {
        printf("you need to specify file path\n");
    }
    return 0;
}