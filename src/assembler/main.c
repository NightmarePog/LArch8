
// main.c
//
// this is entry point of whole program
// it gets arguments proceeds them and later gives output
// made by Lukáš Erl 4/9/2025

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "a_compilation.h"
#include "a_parsing.h"
#include "a_types.h"
#include "file_processer.h"
#include "parser.h"
#include "types.h"

uint64_t make_header(void) {
  uint64_t value = 0;
  value |= (uint64_t)header.signature << 48;
  value |= (uint64_t)header.version << 32;
  value |= (uint64_t)header.reserved_1 << 16;
  value |= (uint64_t)header.reserved_2 << 0;

  return value;
}

void print_tokens(char **program_tokens) {
  if (!program_tokens)
    return;

  for (int i = 0; i != (MAX_TOKENS); i++) {
    printf("%s\n", program_tokens[i]);
  }
  printf("===END OF THE LINE===\n");
}

// divides program into lines, every line into token and after that it gets
// translated into binary
CompilationOutput assemble_program(char **program_pointer) {
  CompilationOutput compilation_output = {0, 0};
  if (!program_pointer)
    return compilation_output;
  char *copy;
  char *tokens[MAX_TOKENS];
  int allocated_size = 5;
  int program_len = 0;
  uint64_t *compiled_program = malloc(allocated_size * sizeof(uint64_t));

  compiled_program[HEADER_LINE] = make_header();
  program_len++;

  for (int i = 0; program_pointer[i] != NULL; i++) {
    program_len++;

    if (allocated_size - i < 4) {
      allocated_size += 10;
      compiled_program =
          realloc(compiled_program, allocated_size * sizeof(uint64_t));
    }

    copy = strdup(program_pointer[i]);
    program_pointer[i] = par_remove_comments(copy);

    if (par_tokenize_line(program_pointer[i], tokens) == 0) {
      compiled_program[i + HEADER_OFFSET] = par_translate_line(tokens);
      printf("[ASSEMBLED LINE] - %lX\n", compiled_program[i + HEADER_OFFSET]);
    } else {
      fprintf(stderr, "tokenization failed\n");
      return compilation_output;
    }
  }
  free(copy);

  compilation_output.program = compiled_program;
  compilation_output.size = program_len;
  return compilation_output;
}

// proceeds the path argument, loads file and tries to assemble it
int init(char *file_path) {
  FILE *file = NULL;
  if (fp_open_file(file_path, &file) == 0) {
    char *program_text = par_get_string_from_file(file);
    char **program_lines = par_str_to_lines(program_text);
    CompilationOutput compilation_result = assemble_program(program_lines);
    if (compilation_result.size != 0) {
      fp_output_program("output.o", compilation_result.program,

                        compilation_result.size);
      fp_output_program_hex("output.hex", compilation_result.program,
                            compilation_result.size);
    }
  } else {
    printf("failed to open file\n");
    return 1;
  }
  fclose(file);
  return 0;
}

int main(int argc, char *argv[]) {
  // controls if path argument exists
  if (argc >= 2) {
    if (init(argv[1]) != 0) {
      printf("failed to compile\n");
      return 1;
    }
  } else {
    printf("you need to specify file path\n");
  }
  return 0;
}