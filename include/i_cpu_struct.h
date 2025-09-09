#pragma once
#include <stdbool.h>
#include <stdint.h>
#define REGISTER_COUNT 4
#define MEMORY_COUNT 512

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
    uint8_t RAM[MEMORY_COUNT];
    uint8_t program_counter;
    FLAGS flags;
    bool halt;
} CPU;

