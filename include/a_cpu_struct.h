#ifndef CPU_STRUCT_H
#define CPU_STRUCT_H

#include <stdint.h>
#include <stdbool.h>

#define REGISTER_COUNT 4

typedef enum {
    R0,
    R1,
    R2,
    R3,
    R4,
} REGISTERS;

typedef enum {
    null_flag,
} FLAGS;

typedef struct {
    uint8_t registers[REGISTER_COUNT];
    uint8_t program_counter;
    FLAGS flags;
    bool halt;
} CPU;

#endif // CPU_STRUCT_H
