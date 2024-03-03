#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 4096

int main(int argc, char * argv[]) {
  if (argc == 1) {
    char buffer[BUFFER_SIZE];
    while (fgets(buffer, BUFFER_SIZE, stdin) != NULL) {
      fputs(buffer, stdout);
    }
    return 0;
  }

  if (!isatty(STDIN_FILENO)) {
    char buffer[BUFFER_SIZE];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, stdin)) > 0) {
      fwrite(buffer, 1, bytesRead, stdout);
    }
    return 0;
  }

  for (int i = 1; i < argc; i++) {
    FILE * file = fopen(argv[i], "r");
    if (file == NULL) {
      perror("Error opening file");
      return EXIT_FAILURE;
    }

    char buffer[BUFFER_SIZE];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
      fwrite(buffer, 1, bytesRead, stdout);
    }

    if (ferror(file)) {
      perror("Error reading file");
      fclose(file);
      return EXIT_FAILURE;
    }
    fclose(file);
  }
  return 0;
}
