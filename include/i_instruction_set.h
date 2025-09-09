#pragma once
#include "i_cpu_struct.h"
#include <stdint.h>
#include <sys/types.h>



typedef void (*InstructionFn)(CPU *, uint8_t *, uint8_t *, uint8_t *);

extern InstructionFn instruction_set[16];