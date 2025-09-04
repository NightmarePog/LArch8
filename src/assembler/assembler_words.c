#include "types.h"
#include <string.h>

DictEntry instruction_set_dict[] = {
    {.key = "NULL", .value = 0x00}, {.key = "ADD", .value = 0x01},
    {.key = "SUB", .value = 0x02},  {.key = "OR", .value = 0x03},
    {.key = "NOT", .value = 0x04},  {.key = "AND", .value = 0x05},
    {.key = "MUL", .value = 0x06},  {.key = "DIV", .value = 0x07},
    {.key = "JE", .value = 0x08},   {.key = "JG", .value = 0x09},
    {.key = "JL", .value = 0x0A},   {.key = "JMP", .value = 0x0B},
    {.key = "HLT", .value = 0x0F},  {.key = NULL, .value = -1}};

DictEntry register_set_dict[] = {
    {.key = "R0", .value = 0x0000}, {.key = "R1", .value = 0x0001},
    {.key = "R2", .value = 0x0002}, {.key = "R3", .value = 0x0003},
    {.key = "R4", .value = 0x0004}, {.key = NULL, .value = -1}};
