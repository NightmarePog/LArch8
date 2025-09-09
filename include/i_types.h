#pragma once
#include "types.h"
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>


typedef struct {
   Header header;
   InstrBin* instrArray;
   size_t size;
   bool success;
} Program;

typedef struct {
   uint8_t *p_address;
   bool is_imm;
} get_p_result;