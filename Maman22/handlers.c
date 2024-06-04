#include "handlers.h"


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/*
    read_set_handler takes a string "str", an array of valid sets "valid_sets" and an array of sets "sets".
    The function checks the syntax of the command (str) and enforces the restrictions of the read_set command structure.
    If the command is valid, the function calls the read_set function with the appropriate arguments.

*/

void read_set_handler(char *str, const char *valid_sets[], set* sets[]) {

    int setIndex; /* The index of the set in the valid_sets array */
    int *setMembers; /* The members of the future set */

    /* Move the pointer past the command name for further analysis */
    str += strlen("read_set");

    /* Skip any (valid) whitespaces until the next significant character */
    skip_spaces(&str);

    /* Check if the set name arguemnt is valid, and if so - get the index of the set in the valid_sets array */
    setIndex = is_valid_set(str, valid_sets, AMOUNT_OF_SETS);


    /* If setIndex is -1, the set name is not a valid one, we return an error and stop */
    if (setIndex == INVALID_VALUE) {
        fprintf(stderr, "[Error] Undefined set name\n");
        return;
    }

    /* Move the pointer past the set name for further analysis */
    str += strlen(valid_sets[setIndex]);

    /* */
    setMembers = retrieve_set_members(str);

    if (setMembers != NULL) {
        read_set(sets[setIndex], setMembers);
        free(setMembers);
    }

}

/*

    print_set_handler takes a string "str", an array of valid sets "valid_sets" and an array of sets "sets".
    The function checks the syntax of the command (str) and enforces the restrictions of the print_set command structure.
    If the command is valid, the function calls the print_set function with the appropriate arguments.

*/

void print_set_handler(char *str, const char *valid_sets[], set* sets[]) {

    int setIndex;

    str += strlen("print_set");

    skip_spaces(&str);


    setIndex = is_valid_set(str, valid_sets, AMOUNT_OF_SETS);

    if (setIndex == INVALID_VALUE) {
        fprintf(stderr, "[Error] Undefined set name\n");
        return;
    }

    /* Check there is nothing but spaces after that */

    str += strlen(valid_sets[setIndex]);

    while (*str != '\0') {
        if (!isspace(*str)) {
            fprintf(stderr, "[Error] Junk values after set name\n");
            return;
        }
        str++;
    }

    print_set(sets[setIndex]);

}

/*

    union_set_handler takes a string "str", an array of valid sets "valid_sets" and an array of sets "sets".
    The function checks the syntax of the command (str) and enforces the restrictions of the union_set command structure.
    If the command is valid, the function calls the union_set function with the appropriate arguments.

*/

void union_set_handler(char *str, const char *valid_sets[], set* sets[]) {

  int *setIndexes;

  str += strlen("union_set");

  setIndexes = retrieve_sets_indexes(str, valid_sets);

  if (setIndexes == NULL) {
    return;
  }

  union_set(sets[setIndexes[0]], sets[setIndexes[1]], sets[setIndexes[2]]);

  free(setIndexes);
}

/*

    intersect_set_handler takes a string "str", an array of valid sets "valid_sets" and an array of sets "sets".
    The function checks the syntax of the command (str) and enforces the restrictions of the intersect_set command structure.
    If the command is valid, the function calls the intersect_set function with the appropriate arguments.

*/

void intersect_set_handler(char *str, const char *valid_sets[], set* sets[]) {

  int *setIndexes;

  str += strlen("intersect_set");

  setIndexes = retrieve_sets_indexes(str, valid_sets);

  if (setIndexes == NULL) {
    return;
  }

  intersect_set(sets[setIndexes[0]], sets[setIndexes[1]], sets[setIndexes[2]]);

  free(setIndexes);
}

/*

    sub_set_handler takes a string "str", an array of valid sets "valid_sets" and an array of sets "sets".
    The function checks the syntax of the command (str) and enforces the restrictions of the sub_set command structure.
    If the command is valid, the function calls the sub_set function with the appropriate arguments.

*/

void sub_set_handler(char *str, const char *valid_sets[], set* sets[]) {

  int *setIndexes;

  str += strlen("sub_set");

  setIndexes = retrieve_sets_indexes(str, valid_sets);

  if (setIndexes == NULL) {
    return;
  }

  sub_set(sets[setIndexes[0]], sets[setIndexes[1]], sets[setIndexes[2]]);

  free(setIndexes);
}

/*

    symdiff_set_handler takes a string "str", an array of valid sets "valid_sets" and an array of sets "sets".
    The function checks the syntax of the command (str) and enforces the restrictions of the symdiff_set command structure.
    If the command is valid, the function calls the symdiff_set function with the appropriate arguments.

*/

void symdiff_set_handler(char *str, const char *valid_sets[], set* sets[]) {

    int *setIndexes;

    str += strlen("symdiff_set");

    setIndexes = retrieve_sets_indexes(str, valid_sets);

    if (setIndexes == NULL) {
      return;
    }

    symdiff_set(sets[setIndexes[0]], sets[setIndexes[1]], sets[setIndexes[2]]);

    free(setIndexes);
}

/*

    stop_handler takes a string "str" and enforces the restrictions of the stop command structure.
    If the command is valid, the function calls the stop function.

*/

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
