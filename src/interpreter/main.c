#include <stdio.h>

int init(char *file_path) { printf("test a, %c", file_path[0]); }

int main(int argc, char *argv[]) {
  printf("hello world\n");
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