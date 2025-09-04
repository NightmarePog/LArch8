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

void print_instruction(INSTR_TRANS_STRUCT *instruction) {
    printf("=========== INSTRUCTION ==============\n");
    printf("OP CODE: %hX\n", instruction->OP_CODE);
    printf("ADR MODE 1: %hX\n", instruction->ADDRESSING_MODE_0);
    printf("ADR MODE 2: %hX\n", instruction->ADDRESSING_MODE_1);
    printf("ADR MODE 3: %hX\n", instruction->ADDRESSING_MODE_2);
    printf("=========== INSTRUCTION END===========\n");
}


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
    int len = strlen(string);
    if (start_offset < 0 || end_offset > len) {
        printf("offset bigger than string size\n");
        return false;
    }

    for (int i = start_offset; i < end_offset; i++) {
        if (!isdigit((unsigned char)string[i])) {
            printf("%d is not a digit\n", string[i]);
            return false;
        }
    }
    return true;
}

int translate_register(char *string) {
    int address_prefix = 2;

    if (string[0] != 'R') {
        return 0;
    }

    switch (string[1]) {
        case '1': return (1 << address_prefix) | 2;
        case '2': return (2 << address_prefix) | 2;
        case '3': return (3 << address_prefix) | 2;
        case '4': return (4 << address_prefix) | 2;
    }
}


static int translate_imm(char *string) __attribute__((unused));
static int translate_imm(char *string) { return 0; }

// returns 0 if failed
// else returns number as address
int translate_address(const char *string) {
    int address_prefix = 3;

    if (!is_anumber(string, 1, -1)) {
        printf("syntax error, %s is not a number in brackets\n", string);
        return 0;
    }

    size_t len = strlen(string);

    // cutting of [ and ]
    char string_copy[5];
    if (len - 2 >= sizeof(string_copy)) {
        printf("number too long\n");
        return 0;
    }

    strncpy(string_copy, string + 1, len - 2);
    string_copy[len - 2] = '\0';

    // translating from string to long
    char *endptr;
    long val = strtol(string_copy, &endptr, 0);

    // checking if success
    if (*endptr != '\0') {
        printf("syntax error, %s is not a valid number\n", string);
        return 0;
    }

    // controlling if value is between 0 and 255
    if (val < 0 || val > 255) {
        printf("value out of range (0-255): %s\n", string);
        return 0;
    }
    printf("[INTERNAL] - VAL: %ld, PREFIX: %d", val, address_prefix);
    return ((int)val << address_prefix) | 2;
}

int translate_line(char **tokenized_line) {
    //uint64_t translated_line = 0;
    INSTR_TRANS_STRUCT instruction;
    uint16_t token_buffer;
    // offset of 12 bits because of instruction start:
    for (int i = 0; i < MAX_TOKENS; i++) {
        switch (i) {
            case OP_CODE: {
                bool found = false;
                for (int k = 0; instruction_set_dict[k].key != NULL; k++) {
                    if (strcmp(instruction_set_dict[k].key, tokenized_line[i]) == 0) {
                        found = true;
                        token_buffer = instruction_set_dict[k].value;
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
                    int size_token = strlen(tokenized_line[i]);
                    char first_token = tokenized_line[i][0];
                    char last_token = tokenized_line[i][size_token-1];
                    if (first_token == '[' || last_token == ']') {
                        // Address
                        printf("[TRANSLATION] [ADDRESS] %s - %X\n", tokenized_line[i], translate_address(tokenized_line[i]));
                        token_buffer = translate_address(tokenized_line[i]);
                    } else if (first_token == 'R') {
                        // Register          
                        printf("[TRANSLATION] [REGISTER] %s - %X\n", tokenized_line[i], translate_register(tokenized_line[i]));
                        token_buffer = translate_register(tokenized_line[i]);    
                    } else if (strtol(tokenized_line[i], NULL, 0)) {
                        // imm
                        printf("[TRANSLATION] [IMM] %s - %X\n", tokenized_line[i], translate_imm(tokenized_line[i]));
                        token_buffer = translate_imm(tokenized_line[i]);
                    }
                }
            

        }
        printf("[%d] - %hX\n", i, token_buffer);
        // max size reached, no need to expand anymore
       /* if (i != MAX_TOKENS-1) { 
            printf("[ADDING] [BEFORE] - [%lX]\n", ((uint64_t)translated_line) << 16);
            translated_line = ((uint64_t)translated_line) << 16; // after expansion sometimes seems like random numbers get generated - FIX error between index 1 and 2
        }
        printf("[ADDING] [AFTER] [%d] - %lX\n", i, translated_line);
        */
        switch (i) {
            case OP_CODE:
                instruction.OP_CODE = token_buffer;
                break;
            case ADDRESSING_MODE_0:
                instruction.ADDRESSING_MODE_0 = token_buffer;
                break;
            case ADDRESSING_MODE_1:
                instruction.ADDRESSING_MODE_1 = token_buffer;
                break;
            case ADDRESSING_MODE_2:
                instruction.ADDRESSING_MODE_2 = token_buffer;
                break;
            default:
                printf("undefined behavior\n - 166 compiler.c");

        
        }
        
    }
    print_instruction(&instruction);
    return 0;
}


