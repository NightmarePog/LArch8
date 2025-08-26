
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "assembler.h"
#include "compiler.h"
#include "string_tools.c"
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


int process_line(char **program_pointer) {
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


int init(char *file_path) {
    FILE *file = NULL;
    if (open_file(file_path, &file) == 0) {
        char *program_text = get_string_from_file(file);
        char **program_lines = tokenize_lines(program_text);
        process_line(program_lines);
    } else {
        printf("failed to open file\n");
        return 1;
    }
    fclose(file);
    return 0;
}

int main(int argc, char *argv[]) {
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