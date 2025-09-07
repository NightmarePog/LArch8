
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

#include "a_addr_translation.h"
#include "a_assembler.h"
#include "a_file_processer.h"
#include "a_types.h"

// debug stuff

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
  int program_size = 5;
  uint64_t *compiled_program = malloc(program_size * sizeof(uint64_t));
  int program_len = 0;

  for (int i = 0; program_pointer[i] != NULL; i++) {
    program_len++;
    if (program_size - i < 4) {
      program_size += 10;
      compiled_program =
          realloc(compiled_program, program_size * sizeof(uint64_t));
    }
    copy = strdup(program_pointer[i]);
    program_pointer[i] = prec_remove_comments(copy); // removing comments
    if (prec_tokenize_line(program_pointer[i], tokens) == 0) {
      compiled_program[i] = prec_translate_line(tokens);
      printf("[ASSEMBLED LINE] - %lX\n", compiled_program[i]);
    } else {
      printf("tokenization failed\n");
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
    char *program_text = prec_get_string_from_file(file);
    char **program_lines = prec_tokenize_lines(program_text);
    CompilationOutput compilation_result = assemble_program(program_lines);
    if (compilation_result.size != 0) {
      fp_output_program("output.o", compilation_result.program,
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