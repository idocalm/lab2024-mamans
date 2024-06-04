#include "set.h"
#include "handlers.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


char *read_line() {
    int position = 0;
    int buffer_size = 1024;
    char *buffer = malloc(sizeof(char) * buffer_size);
    int c;

    if (!buffer) {
        fprintf(stderr, "[Error] couldn't allocate memory\n");
        exit(EXIT_FAILURE);
    }

    while (1) {
        c = getchar();

        if (c == EOF) {
          printf("[Error] Reached EOF\n");
          free(buffer);
          exit(EXIT_FAILURE);
        } else if (c == '\n') {
            buffer[position] = '\0';
            return buffer;
        } else {
            buffer[position] = c;
        }
        position++;

        if (position >= buffer_size) {
            buffer_size += 1024;
            buffer = realloc(buffer, buffer_size);
            if (!buffer) {
                fprintf(stderr, "[Error] couldn't allocate memory\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}






/*

  The main function of the program handles the user input and calls the appropriate functions.
  It also initializes the sets and the valid commands and sets arrays for usage in the command handlers.

*/

int main(int argc, char *argv[]) {

  static set SETA = {{0}, 0};
  static set SETB = {{0}, 0};
  static set SETC = {{0}, 0};
  static set SETD = {{0}, 0};
  static set SETE = {{0}, 0};
  static set SETF = {{0}, 0};

  const char *valid_sets[] = {
      "SETA",
      "SETB",
      "SETC",
      "SETD",
      "SETE",
      "SETF"
  };

  /* The pointers array allows us to access the sets by their names and index */
  set* sets[] = {
      &SETA,
      &SETB,
      &SETC,
      &SETD,
      &SETE,
      &SETF
  };


  const char *valid_commands[] = {
      "read_set",
      "print_set",
      "union_set",
      "intersect_set",
      "sub_set",
      "symdiff_set",
      "stop"
  };


  const command commands_handlers[] = {
    read_set_handler,
    print_set_handler,
    union_set_handler,
    intersect_set_handler,
    sub_set_handler,
    symdiff_set_handler,
    stop_handler
  };


  char* str; /* The user input string */

  int i = 0;

  int command_found = 0; /* A flag that indicates if the command was found */


  while (1) {

    printf("Please enter a command\n");

    str = read_line();

    /* Print the exact input received */
    printf("%s\n", str);

    command_found = 0;



    /* Skip any whitespaces that we're added before the command name */
    skip_spaces(&str);

    /* Loop through valid commands and check for a match */
    for (i = 0; i < AMOUNT_OF_COMMANDS; i++) {
      if (strncmp(str, valid_commands[i], strlen(valid_commands[i])) == 0) {
        /* A match was found, so we call the appropriate handler to analyze the command */
        command_found = 1;
        commands_handlers[i](str, valid_sets, sets);

        break;
      }
    }


    free(str);

    /* If the command was not found, we print an error message */
    if (!command_found) {
      fprintf(stderr, "[Error] Undefined command name\n");
    }


  }
  return 0;
}
