#include "i_cpu_struct.h"
#include "i_instruction_set.h"
#include "i_types.h"
#include "types.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

get_p_result get_p(AdressingMode_type addr_mode, CPU *cpu) {
  get_p_result result;
  if (addr_mode.prefix == IMM) {
    result.is_imm = true;
    return result;
  }
  if (addr_mode.prefix == ADDRESS || addr_mode.prefix == REGIS) {
    result.is_imm = false;
    switch (addr_mode.prefix) {
      case ADDRESS:
        result.p_address = &cpu->RAM[addr_mode.value];
        break;
      case REGIS:
        result.p_address = &cpu->registers[addr_mode.value];
        break;
    }
    return result;
  }
  fprintf(stderr,
          "unknown error while getting pointer on addressing mode, address "
          "type is not defined\n CODE: %d\n",
          addr_mode.prefix);
  result.p_address = NULL;
  return result;
}

void runtime(Program program) {
    CPU cpu = {
        {0},     // REGISTERS
        {0, 0, 0, 0},     // RAM
        0,       // PROGRAM COUNTER
        0,       // FLAGS (UNUSED)
        false,   // HALT
    };

    get_p_result result;
    cpu.halt = false;

    for (; cpu.program_counter < program.size; cpu.program_counter++) {
        if (cpu.halt)
            break;

        InstrBin exe_instr = program.instrArray[cpu.program_counter];
        uint8_t *memory_values[3] = {NULL, NULL, NULL};
        bool is_allocated[3] = {false, false, false};   // které paměti alokovat

        // Získání potřebných adres/hodnot
        for (int i = 0; i < 3; i++) {
            AdressingMode adr_mode;
            switch (i) {
                case 0: adr_mode = exe_instr.ADDRESSING_MODE_0; break;
                case 1: adr_mode = exe_instr.ADDRESSING_MODE_1; break;
                case 2: adr_mode = exe_instr.ADDRESSING_MODE_2; break;
            }

            result = get_p(adr_mode.adr_mode_t, &cpu);

            if (result.is_imm) {
                // Alokujeme přesně 1 byte pro immediate hodnotu
                uint8_t *val = malloc(sizeof(uint8_t));
                if (val == NULL) {
                    fprintf(stderr, "Memory allocation failed!\n");
                    exit(1);
                }
                *val = (uint8_t)adr_mode.adr_mode_t.value;
                memory_values[i] = val;
                is_allocated[i] = true;
            } else {
                // Ukazatel na existující paměť
                if (result.p_address == NULL) {
                    fprintf(stderr, "Invalid memory address at arg %d\n", i);
                    exit(1);
                }
                memory_values[i] = result.p_address;
                is_allocated[i] = false;
            }
        }

        // Debug print
        if (memory_values[0] != NULL)
            printf("value of arg1 is: %d\n", *memory_values[0]);

        // Vykonání instrukce
        instruction_set[exe_instr.OP_CODE](&cpu, memory_values[0], memory_values[1], memory_values[2]);

        // Uvolnění paměti pro immediate hodnoty
        for (int i = 0; i < 3; i++) {
            if (is_allocated[i]) {
                free(memory_values[i]);
            }
        }
        for (int i = 0; i < 4; i++) {
          printf("[MEMORY VALUES]: %d\n", cpu.registers[i]);
        }
    }
}

