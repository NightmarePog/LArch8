#include "file_processer.h"
#include "i_parser.h"
#include "i_runtime.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

int init(char *file_path) {
  FILE *file = NULL;
  if (fp_open_file_bin(file_path, &file) == 0) {
    Program program = par_parse(file);
    runtime(program);
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