#include "i_cpu_struct.h"
#include "i_instruction_set.h"
#include "i_types.h"
#include "types.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>


get_p_result get_p(AdressingMode_type addr_mode) {
   get_p_result result;
   if (addr_mode.prefix == IMM) {
      result.is_imm = true;
      return result;
   }
   if (addr_mode.prefix == ADDRESS || addr_mode.prefix == REGIS) {
      result.is_imm = false;
      result.p_address = &addr_mode.value;
      return result;
   }
   fprintf(stderr, "unknown error while getting pointer on addressing mode, address type is not defined\n CODE: %d\n", addr_mode.prefix);
   result.p_address = NULL;
   return result;
}

void runtime(Program program) {
   CPU cpu;
   for (; cpu.program_counter < program.size; cpu.program_counter++) {
      InstrBin exe_instr = program.instrArray[cpu.program_counter];
      uint8_t* memory_values[3];
      // getting needed memory addresses
      for (int i = 0; i < 3; i++) {
         AdressingMode adr_mode;
         switch (i) {
            case 0:
               adr_mode = exe_instr.ADDRESSING_MODE_0;
               break;
            case 1:
               adr_mode = exe_instr.ADDRESSING_MODE_1;
               break;
            case 2:
               adr_mode = exe_instr.ADDRESSING_MODE_2;
               break;          
         }
         get_p_result result = get_p(adr_mode.adr_mode_t);
         if (result.is_imm == true) {
            memory_values[i] = &adr_mode.adr_mode_t.value;
         } else if (result.is_imm == false) {
            memory_values[i] = result.p_address;
         }
      }
      
      printf("running %X\n", exe_instr.OP_CODE);
      instruction_set[exe_instr.OP_CODE](&cpu, memory_values[0], memory_values[1], memory_values[2]);
   }
}