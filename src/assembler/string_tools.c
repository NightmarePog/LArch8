/*
#include <stdio.h>

long get_file_size(const char *path) {
    FILE *file = fopen(path, "rb");
    if (!file) return -1;            // error opening file

    fseek(file, 0, SEEK_END);
    long size = ftell(file);         // get current position = file size in bytes
    fclose(file);

    return size;
}
*/