#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "a_cpu_struct.h"

typedef void (*InstructionFn)(CPU *, REGISTERS, REGISTERS, REGISTERS);

void instr_null(CPU *cpu, REGISTERS a, REGISTERS b, REGISTERS c);
void instr_add(CPU *cpu, REGISTERS arg1, REGISTERS arg2, REGISTERS reg);
void instr_sub(CPU *cpu, REGISTERS arg1, REGISTERS arg2, REGISTERS reg);
void instr_or(CPU *cpu, REGISTERS arg1, REGISTERS arg2, REGISTERS reg);
void instr_not(CPU *cpu, REGISTERS arg1, REGISTERS arg2, REGISTERS reg);
void instr_and(CPU *cpu, REGISTERS arg1, REGISTERS arg2, REGISTERS reg);
void instr_mul(CPU *cpu, REGISTERS arg1, REGISTERS arg2, REGISTERS reg);
void instr_div(CPU *cpu, REGISTERS arg1, REGISTERS arg2, REGISTERS reg);
void instr_je(CPU *cpu, REGISTERS arg1, REGISTERS arg2, REGISTERS jump_to);
void instr_jg(CPU *cpu, REGISTERS arg1, REGISTERS arg2, REGISTERS jump_to);
void instr_jl(CPU *cpu, REGISTERS arg1, REGISTERS arg2, REGISTERS jump_to);
void instr_jmp(CPU *cpu, REGISTERS arg1, REGISTERS arg2, REGISTERS jump_to);

#endif // INSTRUCTIONS_H
