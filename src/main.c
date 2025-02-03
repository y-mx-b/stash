#include <stdio.h>

char *help() {
  return "Simple dotfile configuration utility.\n"
         "Usage:\n"
         "	<example usage>\n"
         "Options:\n"
         "	<list of options>\n"
         "Commands:\n"
         "	<list of commands>\n";
}

int main(int argc, char **argv) {
  for (int i = 1; i < argc; i++) {
    printf("%s\n", argv[i]);
  }

  if (argc == 1) {
    printf("%s", help());
  }
}
