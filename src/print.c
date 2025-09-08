#include <stdint.h>
#include <stdio.h>
#include <string.h>



void pr_print_text_hex(const uint64_t *program_hex, size_t count) {
    for (size_t i = 0; i < count; i++) {
        printf("0x%016lX\n", program_hex[i]);
    }
}