#include <stdio.h>
#include <stdlib.h>
#include <string.h>



// Copies a string into a new dynamically allocated buffer.
char* read_string(const char *str) {
    if (!str) return NULL;
    size_t len = strlen(str);
    char *buffer = malloc(len + 1);
    if (!buffer) return NULL;
    strcpy(buffer, str);
    return buffer;
}

long get_file_size(const char *path) {
    FILE *file = fopen(path, "rb");  // open in binary mode
    if (!file) return -1;            // error opening file

    fseek(file, 0, SEEK_END);        // move to the end of the file
    long size = ftell(file);         // get current position = file size in bytes
    fclose(file);

    return size;
}
