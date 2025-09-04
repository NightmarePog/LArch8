#include "assembler.h"
#include "assembler_words.h"
#include "addr_translation.h"


#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_LINE_SIZE 128
#define MAX_TOKENS 4



uint64_t assemble_instruction(INSTR_TRANS_STRUCT *instr) {
    uint64_t assembled_instruction = 0;

    assembled_instruction |= ((uint64_t)instr->OP_CODE)           << 48;
    assembled_instruction |= ((uint64_t)instr->ADDRESSING_MODE_0) << 32;
    assembled_instruction |= ((uint64_t)instr->ADDRESSING_MODE_1) << 16;
    assembled_instruction |= ((uint64_t)instr->ADDRESSING_MODE_2) << 0;

    printf("[ASSEMBLED LINE]: %016llX\n", (unsigned long long)assembled_instruction);
    return assembled_instruction;
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
                printf("undefined behavior\n - 201 compiler.c");

        
        }
        assemble_instruction(&instruction);
        
    }
    print_instruction(&instruction);
    return 0;
}


