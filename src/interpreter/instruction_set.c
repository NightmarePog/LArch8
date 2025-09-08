#include <stdbool.h>
#include <stdint.h>
#include "a_cpu_struct.h"


typedef void (*InstructionFn)(CPU *, REGISTERS, REGISTERS, REGISTERS);



static void instr_null(CPU *cpu, REGISTERS a, REGISTERS b, REGISTERS c) {}


static void instr_add(CPU *cpu, REGISTERS arg1, REGISTERS arg2, REGISTERS reg) {
    cpu->registers[reg] = cpu->registers[arg1] + cpu->registers[arg2];
}

static void instr_sub(CPU *cpu, REGISTERS arg1, REGISTERS arg2, REGISTERS reg) {
    cpu->registers[reg] = cpu->registers[arg1] - cpu->registers[arg2];
}

static void instr_or(CPU *cpu, REGISTERS arg1, REGISTERS arg2, REGISTERS reg) {
    cpu->registers[reg] = cpu->registers[arg1] | cpu->registers[arg2];
}

static void instr_not(CPU *cpu, REGISTERS arg1, REGISTERS arg2, REGISTERS reg) {
    cpu->registers[reg] = !cpu->registers[arg1];
}

static void instr_and(CPU *cpu, REGISTERS arg1, REGISTERS arg2, REGISTERS reg) {
    cpu->registers[reg] = cpu->registers[arg1] & cpu->registers[arg2];
}

static void instr_mul(CPU *cpu, REGISTERS arg1, REGISTERS arg2, REGISTERS reg) {
    cpu->registers[reg] = cpu->registers[arg1] * cpu->registers[arg2];
}

static void instr_div(CPU *cpu, REGISTERS arg1, REGISTERS arg2, REGISTERS reg) {
    cpu->registers[reg] = cpu->registers[arg1] / cpu->registers[arg2];
}

static void instr_je(CPU *cpu, REGISTERS arg1, REGISTERS arg2, REGISTERS jump_to) {
    if (cpu->registers[arg1] == cpu->registers[arg2]) {
        cpu->program_counter = jump_to;
    }
}

static void instr_jg(CPU *cpu, REGISTERS arg1, REGISTERS arg2, REGISTERS jump_to) {
    if (cpu->registers[arg1] > cpu->registers[arg2]) {
        cpu->program_counter = jump_to;
    }
}

static void instr_jl(CPU *cpu, REGISTERS arg1, REGISTERS arg2, REGISTERS jump_to) {
    if (cpu->registers[arg1] < cpu->registers[arg2]) {
        cpu->program_counter = jump_to;
    }
}

static void instr_jmp(CPU *cpu, REGISTERS arg1, REGISTERS arg2, REGISTERS jump_to) {
    cpu->program_counter = jump_to;
}

static void instr_halt(CPU *cpu, REGISTERS arg1, REGISTERS arg2, REGISTERS jump_to) {
    cpu->halt = true
}

InstructionFn instruction_set[16] = {
    [0x00] = instr_null,
    [0x01] = instr_add,
    [0x02] = instr_sub,
    [0x03] = instr_or,
    [0x04] = instr_not,
    [0x05] = instr_and,
    [0x06] = instr_mul,
    [0x07] = instr_div,
    [0x08] = instr_je,
    [0x09] = instr_jg,
    [0x0A] = instr_jl,
    [0x0B] = instr_jmp,
    [0x0C] = instr_null,
    [0x0D] = instr_null,
    [0x0E] = instr_null,
    [0x0F] = instr_null,
};