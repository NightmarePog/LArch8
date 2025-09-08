#include "types.h"
#include <stddef.h>
#include <stdint.h>


typedef struct {
   Header header;
   InstrBin* instrArray;
   size_t size;
} Program;

