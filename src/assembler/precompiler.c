
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LINE_LEN 64
#define MAX_LINES 256

// cuts of the comment
char* rem_comms_in_line(char* line) {
    char* comment_start = strchr(line, ';');
    if (comment_start != NULL) {
        *comment_start = '\0';
    }
    return line;
}

// gets whole line file input and tokenize it into lines
char** tokenize_lines(char* input) {
    int capacity = 4;  // start up line length
    char **lines = malloc(capacity * sizeof(char*));
    int count = 0;

    while (*input != '\0') {
        // find line lenght
        int len = 0;
        char *start = input;
        while (input[len] != '\n' && input[len] != '\0') {
            len++;
        }

        // allocate memory for that line according to it's length
        char *line = malloc(len + 1);
        strncpy(line, start, len);
        line[len] = '\0';

        // if there are more lines and start up capacity it allocates
        if (count >= capacity) {
            capacity *= 2;
            char **tmp = realloc(lines, capacity * sizeof(char*));
            if (!tmp) {
                // error handling
                for (int i = 0; i < count; i++) free(lines[i]);
                free(lines);
                return NULL;
            }
            lines = tmp;
        }

        lines[count++] = line;

        input += len;
        if (*input == '\n') input++;  // skip new line lol
    }
    return lines;
}

// gets file and returns string
char* get_string_from_file(FILE *file) {
    if (!file) return NULL;

    // get size of file
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    if (size < 0) return NULL;  // error thingy :3

    fseek(file, 0, SEEK_SET);

    // buffer allocation
    char *buffer = malloc(size + 1);
    if (!buffer) return NULL;

    // this will load the file
    size_t read_size = fread(buffer, 1, size, file);
    buffer[read_size] = '\0';  // ends the string

    return buffer;
}

