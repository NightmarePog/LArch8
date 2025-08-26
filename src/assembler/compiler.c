#include "assembler.h"
#include "assembler_words.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_SIZE 128
#define MAX_TOKENS 4

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

bool is_anumber(const char *string, int start_offset, int end_offset) {
    int size_string = sizeof(*string);
    for (int i = 0+start_offset; i < size_string+end_offset; i++) {
        if (!isdigit(string[i])) {
            return false;
        }
    }
    return true;
}

static int translate_register(char *string) __attribute__((unused));
static int translate_register(char *string) { return 0; }


static int translate_imm(char *string) __attribute__((unused));
static int translate_imm(char *string) { return 0; }

// returns 0 if failed
// else returns number as address
static int translate_address(const char *string) {
    int address_prefix = 3;
    if (!is_anumber(string, 1, -1)) {
        printf("syntax error, %s is not a number\n", string);
        return 0;
    }

    // buffer - biggest number should be 255
    char string_copy[3];
    strncpy(string_copy, string, sizeof(string_copy) - 1);
    string_copy[sizeof(string_copy) - 1] = '\0';

    long val = strtol(string_copy, NULL, 0);

    // if is 8 bit num
    if (val < 0 || val > 255) {
        printf("value out of range (0-255): %s\n", string);
        return 0;
    }

    return (int) (address_prefix << 3) | val;;
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
            case ADDRESSING_MODE_0:
            case ADDRESSING_MODE_1:
            case ADDRESSING_MODE_2: {
                    int size_token = sizeof(*tokenized_line[i]);
                    char first_token = tokenized_line[i][0];
                    char last_token = tokenized_line[i][size_token-1];
                    if (first_token == '[' || last_token == ']') {
                        // Address
                        translated_line += translate_address(tokenized_line[i]);
                    } else if (first_token == 'R') {
                        // Register          
                        translated_line += translate_register(tokenized_line[i]);    
                    } else if (strtol(tokenized_line[i], NULL, 0)) {
                        translated_line += translate_imm(tokenized_line[i]);
                    }
                }
            

        }
        if (i != MAX_TOKENS-1) {
            translated_line = ((uint32_t)translated_line) << 8;
        }

        
    }
    printf("translated to %X\n", translated_line);
    return 0;
}