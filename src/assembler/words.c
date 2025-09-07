/*
assembler_words.c
this is dictionary of words and their hex value so it's easy for assembler to
translate them made by Lukáš Erl 4/9/2025
*/

#include "a_types.h"
#include <string.h>

DictEntry const instruction_set_dict[] = {
    {.key = "NULL", .value = 0x00}, {.key = "ADD", .value = 0x01},
    {.key = "SUB", .value = 0x02},  {.key = "OR", .value = 0x03},
    {.key = "NOT", .value = 0x04},  {.key = "AND", .value = 0x05},
    {.key = "MUL", .value = 0x06},  {.key = "DIV", .value = 0x07},
    {.key = "JE", .value = 0x08},   {.key = "JG", .value = 0x09},
    {.key = "JL", .value = 0x0A},   {.key = "JMP", .value = 0x0B},
    {.key = "HLT", .value = 0x0F},  {.key = NULL, .value = -1}};
