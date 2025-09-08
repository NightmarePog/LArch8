#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char** p_split_lines(const char *program) {
}

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint64_t* par_get_binary_file(FILE *file, size_t *out_count) {
    if (!file) return NULL;

    if (fseek(file, 0, SEEK_END) != 0) return NULL;
    long size_long = ftell(file);
    if (size_long < 0) return NULL;
    uint64_t size = (uint64_t)size_long;
    fseek(file, 0, SEEK_SET);

    size_t count = size / sizeof(uint64_t);
    if (count == 0) return NULL;

    uint64_t *buffer = (uint64_t*)malloc(count * sizeof(uint64_t));
    if (!buffer) return NULL;

    if (fread(buffer, sizeof(uint64_t), count, file) != count) {
        free(buffer);
        return NULL;
    }

    if (out_count) *out_count = count;
    return buffer;
}
