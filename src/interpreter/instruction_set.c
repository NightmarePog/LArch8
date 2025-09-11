#include "i_cpu_struct.h"
#include "i_instruction_set.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

// NOP
static void instr_null(CPU *cpu, uint8_t *a, uint8_t *b, uint8_t *c) {}

// ADD
static void instr_add(CPU *cpu, uint8_t *arg1, uint8_t *arg2, uint8_t *reg) {
  cpu->registers[*reg] = cpu->registers[*arg1] + cpu->registers[*arg2];
}

// SUB
static void instr_sub(CPU *cpu, uint8_t *arg1, uint8_t *arg2, uint8_t *reg) {
  cpu->registers[*reg] = cpu->registers[*arg1] - cpu->registers[*arg2];
}

// OR
static void instr_or(CPU *cpu, uint8_t *arg1, uint8_t *arg2, uint8_t *reg) {
  cpu->registers[*reg] = cpu->registers[*arg1] | cpu->registers[*arg2];
}

// NOT
static void instr_not(CPU *cpu, uint8_t *arg1, uint8_t *arg2, uint8_t *reg) {
  cpu->registers[*reg] = !cpu->registers[*arg1];
}

// AND
static void instr_and(CPU *cpu, uint8_t *arg1, uint8_t *arg2, uint8_t *reg) {
  cpu->registers[*reg] = cpu->registers[*arg1] & cpu->registers[*arg2];
}

// MUL
static void instr_mul(CPU *cpu, uint8_t *arg1, uint8_t *arg2, uint8_t *reg) {
  cpu->registers[*reg] = cpu->registers[*arg1] * cpu->registers[*arg2];
}

// DIV
static void instr_div(CPU *cpu, uint8_t *arg1, uint8_t *arg2, uint8_t *reg) {
  cpu->registers[*reg] = cpu->registers[*arg1] / cpu->registers[*arg2];
}

// JE
static void instr_je(CPU *cpu, uint8_t *arg1, uint8_t *arg2, uint8_t *jump_to) {
  if (cpu->registers[*arg1] == cpu->registers[*arg2]) {
    cpu->program_counter = *jump_to;
  }
}

// JG
static void instr_jg(CPU *cpu, uint8_t *arg1, uint8_t *arg2, uint8_t *jump_to) {
  if (cpu->registers[*arg1] > cpu->registers[*arg2]) {
    cpu->program_counter = *jump_to;
  }
}

// JL
static void instr_jl(CPU *cpu, uint8_t *arg1, uint8_t *arg2, uint8_t *jump_to) {
  if (cpu->registers[*arg1] < cpu->registers[*arg2]) {
    cpu->program_counter = *jump_to;
  }
}

// JMP
static void instr_jmp(CPU *cpu, uint8_t *arg1, uint8_t *arg2,
                      uint8_t *jump_to) {
  cpu->program_counter = *jump_to;
}

static void instr_prnt(CPU *cpu, uint8_t *arg1, uint8_t *arg2,
                       uint8_t *jump_to) {
  printf("printing: %d\n", *arg1);
}

// MOV
static void instr_mov(CPU *cpu, uint8_t *arg1, uint8_t *arg2, uint8_t *arg3) {
  printf("ARG1: %d\n ARG2: %d\n", *arg1, *arg2);
  *arg1 = *arg2;
}
// HALT
static void instr_halt(CPU *cpu, uint8_t *arg1, uint8_t *arg2,
                       uint8_t *jump_to) {
  cpu->halt = true;
}

InstructionFn instruction_set[16] = {
    [0x00] = instr_null, [0x01] = instr_add,  [0x02] = instr_sub,
    [0x03] = instr_or,   [0x04] = instr_not,  [0x05] = instr_and,
    [0x06] = instr_mul,  [0x07] = instr_div,  [0x08] = instr_je,
    [0x09] = instr_jg,   [0x0A] = instr_jl,   [0x0B] = instr_jmp,
    [0x0C] = instr_prnt, [0x0D] = instr_mov, [0x0E] = instr_null,
    [0x0F] = instr_halt,
};