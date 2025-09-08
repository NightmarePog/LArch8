#ifndef GLOBAL_TYPES
#define GLOBAL_TYPES

#include <stdint.h>

#define MAX_TOKENS    4
#define MAX_LINES     256
#define MAX_LINE_LEN  64
#define VERSION 1
#define HEADER_SIGNATURE 0xFFFF
#define HEADER_OFFSET 1
#define HEADER_LINE 0
typedef struct {
    const char *key;
    int value;
} DictEntry;

typedef struct {
    uint8_t prefix;
    uint8_t value;
} AdressingMode_type;

typedef union {
    uint16_t uint16_t;
    AdressingMode_type adr_mode_t;
} AdressingMode;

typedef struct {
    uint16_t OP_CODE;
    AdressingMode ADDRESSING_MODE_0;
    AdressingMode ADDRESSING_MODE_1;
    AdressingMode ADDRESSING_MODE_2;

} InstrBin;

typedef struct {
    uint16_t signature;
    uint16_t version;
    uint16_t reserved_1;
    uint16_t reserved_2;

} Header;

extern const Header header;

enum ADDRESS_MODE_PREFIX {
   IMM = 1,
   REGIS = 2,
   ADDRESS = 3,

};

extern DictEntry const instruction_set_dict[];

#endif