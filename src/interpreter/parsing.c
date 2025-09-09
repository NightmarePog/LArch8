#include "types.h"
#include "i_types.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_instr(const InstrBin* instr, int index) {
    printf("Instr[%d]: OP_CODE=%X, ADDR0={prefix:%X, value:%X}, ADDR1={prefix:%X, value:%X}, ADDR2={prefix:%X, value:%X}\n",
            index,
            instr->OP_CODE,
            instr->ADDRESSING_MODE_0.adr_mode_t.prefix,
            instr->ADDRESSING_MODE_0.adr_mode_t.value,
            instr->ADDRESSING_MODE_1.adr_mode_t.prefix,
            instr->ADDRESSING_MODE_1.adr_mode_t.value,
            instr->ADDRESSING_MODE_2.adr_mode_t.prefix,
            instr->ADDRESSING_MODE_2.adr_mode_t.value);
}

void print_program(const Program* program) {
    printf("=== HEADER ===\n");
    printf("Signature : 0x%04X\n", program->header.signature);
    printf("Version   : %u\n", program->header.version);
    printf("Reserved1 : %u\n", program->header.reserved_1);
    printf("Reserved2 : %u\n", program->header.reserved_2);

    printf("\n=== INSTRUCTIONS (count=%zu) ===\n", program->size);
    for (uint16_t i = 0; i < program->size; i++) {
        print_instr(&program->instrArray[i], i);
    }
}


Header parse_header(uint64_t raw) {
    Header h;

    h.signature  = (raw >> 48) & 0xFFFF;
    h.version    = (raw >> 32) & 0xFFFF;
    h.reserved_1 = (raw >> 16) & 0xFFFF;
    h.reserved_2 = (raw >>  0) & 0xFFFF;

    return h;
}

InstrBin parse_instr(uint64_t raw) {
    InstrBin i;

    i.OP_CODE = (raw >> 48) & 0xFFFF;

    // ADDRESSING_MODE_0
    i.ADDRESSING_MODE_0.adr_mode_t.prefix = (raw >> 40) & 0xFF;
    i.ADDRESSING_MODE_0.adr_mode_t.value  = (raw >> 32) & 0xFF;

    // ADDRESSING_MODE_1
    i.ADDRESSING_MODE_1.adr_mode_t.prefix = (raw >> 24) & 0xFF;
    i.ADDRESSING_MODE_1.adr_mode_t.value  = (raw >> 16) & 0xFF;

    // ADDRESSING_MODE_2
    i.ADDRESSING_MODE_2.adr_mode_t.prefix = (raw >> 8) & 0xFF;
    i.ADDRESSING_MODE_2.adr_mode_t.value  = (raw >> 0) & 0xFF;
    return i;
}



uint64_t* get_binary_file(FILE *file, size_t *out_count) {
    if (!file) return NULL;

    if (fseek(file, 0, SEEK_END) != 0) return NULL;
    long size_long = ftell(file);
    if (size_long < 0) return NULL;
    uint64_t size = (uint64_t)size_long;
    fseek(file, 0, SEEK_SET);

    size_t count = size / sizeof(uint64_t);
    if (count == 0) return NULL;

    uint64_t *buffer = (uint64_t*)malloc(count * sizeof(uint64_t));
    if (!buffer) return NULL;

    if (fread(buffer, sizeof(uint64_t), count, file) != count) {
        free(buffer);
        return NULL;
    }

    if (out_count) *out_count = count;
    return buffer;
}


Program par_parse(FILE *file) {
    Program program;
    size_t allocated = 5;
    program.instrArray = malloc(sizeof(InstrBin)*allocated);
    uint64_t *raw_program = get_binary_file(file, &program.size);
    for (size_t i = 0; i < program.size; i++) {
        if (allocated-i < 4) {
            allocated += 10;
            program.instrArray = realloc(program.instrArray, allocated*sizeof(InstrBin));
        }
        if (i == HEADER_LINE) {
            program.header = parse_header(raw_program[i]);
            continue;
        }
        program.instrArray[i-HEADER_OFFSET] = parse_instr(raw_program[i]);
        printf("program size: %zu\n", program.size);
    }

    program.size -= 1;
    if (program.header.version != VERSION) {
        fprintf(stderr, "Program version diffrence\n program version: %d\n interpreter version: %d\n", program.header.version, VERSION);
        program.success = false;
        return program;
    }
    print_program(&program);
    program.success = true;
    return program;

}
