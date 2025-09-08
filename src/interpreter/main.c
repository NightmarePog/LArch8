#include <stdio.h>
#include "file_processer.h"
#include "parser.h"

int init(char *file_path) {
  FILE *file = NULL;
  if (fp_open_file(file_path, &file) == 0) {
    char *program_text = par_get_string_from_file(file);
    char **program_lines = par_str_to_lines(program_text);
    // TODO PARSED
    printf("program text: %s\n", program_text);
    // print_tokens(program_lines); -- i'll make function for that
    return 0;
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