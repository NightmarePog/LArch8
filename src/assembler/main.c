
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "assembler.h"
#include "string_tools.c"
#define MAX_LINE_SIZE 128
#define MAX_TOKENS 4


// debug stuff

void read_file(FILE *file) {
    char line[MAX_LINE_SIZE];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
}

int open_file(char *file_path, FILE **file_pointer) {
    FILE *file = fopen(file_path, "r");

    *file_pointer = file;
    return !file;
}

void print_tokens(char **program_tokens) {
    if (!program_tokens) return;

    for (int i = 0; i != (MAX_TOKENS-1); i++) {
        printf("%s\n", program_tokens[i]);
    }
    printf("===END OF THE LINE===\n");
}

int translate_line(char **tokenized_line) {
    int translated_line = 0;
    for (int i = 0; i < MAX_TOKENS; i++) {
        switch (i) {
            case OP_CODE: {
                bool found = false;
                for (int k = 0; instruction_set_dict[k].key != NULL; k++) {
                    if (strcmp(instruction_set_dict[k].key, tokenized_line[i]) == 0) {
                        found = true;
                        translated_line += instruction_set_dict[k].value;
                        break;
                    }
                }
                if (!found) {
                    printf("Unknown opcode: %s\n", tokenized_line[i]);
                }
                break;
            }
        }

        translated_line = ((uint16_t)translated_line) << 8;

        
    }
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