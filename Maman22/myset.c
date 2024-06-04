#include "set.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


char *read_line() {
    int bufsize = 1024;
    int position = 0;
    char *buffer = malloc(sizeof(char) * bufsize);
    int c;

    if (!buffer) {
        fprintf(stderr, "read_line: allocation error\n");
        exit(EXIT_FAILURE);
    }

    while (1) {
        c = getchar();

        if (c == EOF || c == '\n') {
            buffer[position] = '\0';
            return buffer;
        } else {
            buffer[position] = c;
        }
        position++;

        if (position >= bufsize) {
            bufsize += 1024;
            buffer = realloc(buffer, bufsize);
            if (!buffer) {
                fprintf(stderr, "read_line: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

void skip_spaces(char **str) {
    while (isspace(**str)) {
        (*str)++;
    }
}


int is_valid_set(char *str, const char *valid_sets[], int num_sets) {
    int i = 0;

    for (; i < num_sets; i++) {
        if (strncmp(str, valid_sets[i], strlen(valid_sets[i])) == 0) {
            return i;
        }
    }

    return -1;
}

int* validate_read_set(char *str) {

    int current_num = 0;
    int seen_ending = 0;

    int* set_members = NULL;
    int set_members_size = 0;

    skip_spaces(&str);

    if (*str != ',') {
        printf("[Error] No comma after set name\n");
        return NULL;
    }

    str++;


    /* Loop for comma-separated numbers */
    while (*str != '\0') {

        skip_spaces(&str);

        if (*str == '-') {
          str++;
          if (*str == '1') {
            seen_ending = 1;
            break;
          } else {
            printf("[Error] Invalid set member - not an integer: %c\n", *str);
            return NULL;
          }
        }


        if (!isdigit(*str)) {
            printf("[Error] Invalid set member - not an integer: %c\n", *str);
            return NULL;
        }

        /* Handle multi-digit numbers */
        current_num = 0;
        while (isdigit(*str)) {
          current_num = current_num * 10 + (*str - '0');
          str++;
        }

        /* Add current_num to set_members */
        set_members_size++;
        set_members = (int*) realloc(set_members, set_members_size * sizeof(unsigned int));
        set_members[set_members_size - 1] = current_num;



        if (*str != ',' && *str != ' ' && *str != '\0') {
          printf("[Error] Invalid set member - not an integer: %c\n", *str);
          return NULL;
        }

        if (current_num < 0 || current_num > 127) {
            printf("[Error] Invalid set member - value out of range: %d\n", current_num);
            return NULL;
        }



        /* Find the next comma or end marker */

        while (*str != ',' && *str != '\0') {
            str++;
        }

        if (*str == '\0') {
          printf("[Error] List of set members is not terminated correctly\n");
          return NULL;
        }

        /* Check for double comma */

        if (*str == ',' && *(str + 1) == ',') {
            printf("[Error] Multiple consecutive commas\n");
            return NULL;
        }

        /* Move to next element after the comma / end marker */

        if (*str == ',') {
            str++;
        }
    }
    str++;

    if (seen_ending) {
        /* Check there are no junk values */
        printf("%c", *str);
        while (*str != '\0') {
            if (!isspace(*str)) {
                printf("[Error] Junk values after -1\n");
                return NULL;
            }
            str++;
        }

        /* Push a sentinal */

        set_members_size++;
        set_members = (int*) realloc(set_members, set_members_size * sizeof(unsigned int));
        set_members[set_members_size - 1] = -1;

        return set_members;
    }



    return NULL;

}


void read_set_handler(char *str, const char *valid_sets[], set* sets[]) {

    int setIndex;
    int *setMembers;

    str += strlen("read_set");

    skip_spaces(&str);

    setIndex = is_valid_set(str, valid_sets, AMOUNT_OF_SETS);


    if (setIndex == -1) {
        printf("[Error] Undefined set name\n");
    }

    str += strlen(valid_sets[setIndex]);

    setMembers = validate_read_set(str);

    if (setMembers != NULL) {
        read_set(sets[setIndex], setMembers);
        free(setMembers);
    }

}

void print_set_handler(char *str, const char *valid_sets[], set* sets[]) {

    int setIndex;

    str += strlen("print_set");

    skip_spaces(&str);


    setIndex = is_valid_set(str, valid_sets, AMOUNT_OF_SETS);

    if (setIndex == -1) {
        printf("[Error] Undefined set name\n");
        return;
    }

    /* Check there is nothing but spaces after that */

    str += strlen(valid_sets[setIndex]);

    while (*str != '\0') {
        if (!isspace(*str)) {
            printf("[Error] Junk values after set name\n");
            return;
        }
        str++;
    }

    print_set(sets[setIndex]);

}


int* retrieve_sets_indexes(char *str, const char *valid_sets[]) {
    int i = 0;

    int *setIndexes = (int*) malloc(3 * sizeof(int));

    for (; i < 2; i++) {
        skip_spaces(&str);

        setIndexes[i] = is_valid_set(str, valid_sets, AMOUNT_OF_SETS);

        if (setIndexes[i] == -1) {
            printf("[Error] Undefined set name\n");
            free(setIndexes);
            return NULL;
        }

        str += strlen(valid_sets[setIndexes[i]]);

        skip_spaces(&str);

        if (*str != ',') {
            printf("[Error] No comma after set name\n");
            free(setIndexes);
            return NULL;
        }

        str++;
    }

    skip_spaces(&str);

    setIndexes[2] = is_valid_set(str, valid_sets, AMOUNT_OF_SETS);

    if (setIndexes[2] == -1) {
        printf("[Error] Undefined set name\n");
        free(setIndexes);
        return NULL;
    }

    str += strlen(valid_sets[setIndexes[2]]);

    skip_spaces(&str);

    while (*str != '\0') {
      if (!isspace(*str)) {
          printf("[Error] Junk values after set names\n");
          free(setIndexes);
          return NULL;
      }
      str++;
    }

    return setIndexes;
}

void union_set_handler(char *str, const char *valid_sets[], set* sets[]) {

  str += strlen("union_set");

  int *setIndexes = retrieve_sets_indexes(str, valid_sets);

  if (setIndexes == NULL) {
    return;
  }

  union_set(sets[setIndexes[0]], sets[setIndexes[1]], sets[setIndexes[2]]);

  free(setIndexes);
}

void intersect_set_handler(char *str, const char *valid_sets[], set* sets[]) {

  str += strlen("intersect_set");

  int *setIndexes = retrieve_sets_indexes(str, valid_sets);

  if (setIndexes == NULL) {
    return;
  }

  intersect_set(sets[setIndexes[0]], sets[setIndexes[1]], sets[setIndexes[2]]);

  free(setIndexes);
}

void sub_set_handler(char *str, const char *valid_sets[], set* sets[]) {

  str += strlen("sub_set");

  int *setIndexes = retrieve_sets_indexes(str, valid_sets);

  if (setIndexes == NULL) {
    return;
  }

  sub_set(sets[setIndexes[0]], sets[setIndexes[1]], sets[setIndexes[2]]);

  free(setIndexes);
}

void symdiff_set_handler(char *str, const char *valid_sets[], set* sets[]) {

    str += strlen("symdiff_set");

    int *setIndexes = retrieve_sets_indexes(str, valid_sets);

    if (setIndexes == NULL) {
      return;
    }

    symdiff_set(sets[setIndexes[0]], sets[setIndexes[1]], sets[setIndexes[2]]);

    free(setIndexes);
}

void stop_handler(char *str) {
  str += strlen("stop");

  /* Check there is nothing but spaces after that */

  while (*str != '\0') {
      if (!isspace(*str)) {
          printf("[Error] Junk values after stop\n");
          return;
      }
      str++;
  }

  stop();
}



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


  const CommandHandler commands_handlers[] = {
    read_set_handler,
    print_set_handler,
    union_set_handler,
    intersect_set_handler,
    sub_set_handler,
    symdiff_set_handler,
    stop_handler
  };


  char* str;

  int i = 0;

  int command_found = 0;

  int run = 1;

  while (run) {

    printf("Please enter a command\n");

    str = read_line();

    command_found = 0;

    if (!str) {
      /* EOF */
      printf("[Error] Reached EOF\n");
      free(str);
      run = 0;
    }

    skip_spaces(&str); /* Skip any whitespaces that we're added before the command name */

    for (i = 0; i < AMOUNT_OF_COMMANDS; i++) {
      if (strncmp(str, valid_commands[i], strlen(valid_commands[i])) == 0) {
        command_found = 1;
        commands_handlers[i](str, valid_sets, sets);

        break;
      }
    }

    free(str);

    if (!command_found) {
      printf("[Error] Undefined command name\n");
    }


  }
  return 0;
}
