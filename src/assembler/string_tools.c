#include <stdio.h>

long get_file_size(const char *path) {
    FILE *file = fopen(path, "rb");  // open in binary mode
    if (!file) return -1;            // error opening file

    fseek(file, 0, SEEK_END);        // move to the end of the file
    long size = ftell(file);         // get current position = file size in bytes
    fclose(file);

    return size;
}
