
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MIN_SET_VALUE 0
#define MAX_SET_VALUE 127
#define SETS_PER_COMMAND 3
#define AMOUNT_OF_SETS 6
#define INVALID_VALUE -1

/*
    skip_spaces takes a pointer to a string "str" and skips all the spaces in the string.
    Eventually, the pointer will point to the first non-space character in the string.
*/

void skip_spaces(char **str) {
    while (isspace(**str)) {
        (*str)++;
    }
}

/*
    is_valid_set takes a string "str", an array of valid sets "valid_sets" and the number of sets "num_sets".
    The function checks if the string is a valid set name, and returns the index of the set in the array if it is, and -1 otherwise.
*/

int is_valid_set(char *str, const char *valid_sets[], int num_sets) {
    int i = 0;

    for (; i < num_sets; i++) {
        /* Check if the string starts with the current valid set name */
        if (strncmp(str, valid_sets[i], strlen(valid_sets[i])) == 0) {
            return i;
        }
    }

    /* No valid set name found */
    return -1;
}


/*
    retrieve_set_members takes a string "str" and retrieves the set members from it.
    The function checks the syntax of the set members and enforces the restrictions of the set members structure.
    If the set members are valid, the function returns an array of the set members.
    If the set members are invalid, the function returns a NULL pointer.

    This function is used for commands that require a set name and a list of set members (read_set).
*/

int* retrieve_set_members(char *str) {

    int current_num = 0; /* Current number being read */
    int is_negative = 0; /* Flag to check if the number is negative */
    int seen_ending = 0; /* Flag to check if -1 was seen */

    int* set_members = NULL; /* Array to store the future set members */
    int set_members_size = 0; /* Size of the set_members array */

    /* Skip any (valid) whitespaces until the next significant character */
    skip_spaces(&str);

    /* If the pointer doesn't point to a comma, the command is illegal. We return an error and stop */
    if (*str != ',') {
        fprintf(stderr, "[Error] No comma after set name\n");
        return NULL;
    }

    /* Skip the comma */
    str++;


    /* Loop for comma-separated numbers */
    while (*str != '\0' && !seen_ending) {

        /* Skip any (valid) whitespaces until the next significant character */
        skip_spaces(&str);

        /* Reset the negative flag */
        is_negative = 0;


        if (*str == '-') {
          is_negative = 1;
          str++;
          if (*str == '1') {
            str++;
            seen_ending = 1;
            break;
          }
        }

        /* If the pointer doesn't point to a digit, the command is illegal. We return an error and stop */
        if (!isdigit(*str)) {
            fprintf(stderr, "[Error] Invalid set member - not an integer: %c\n", *str);
            return NULL;
        }

        /* Numbers can be more than one digit, so we loop until we reach a non-digit character */
        current_num = 0;
        while (isdigit(*str)) {
            /* Move all digits of current_num one palce left and add the new digit */
            current_num = current_num * 10 + (*str - '0');
            str++;
        }

        if (is_negative) {
          current_num *= -1;
        }

        /* Increase the size of the set_members array by one to fit the new number */
        set_members_size++;
        set_members = (int*) realloc(set_members, set_members_size * sizeof(unsigned int));

        /* If the allocation failed, we return an error and stop */
        if (!set_members) {
            fprintf(stderr, "[Error] couldn't allocate memory\n");
            exit(EXIT_FAILURE);
        }

        /* Add the current number to the set_members array */
        set_members[set_members_size - 1] = current_num;

        /* 
            If we reached the end of the number, and there is no comma or a space, the command is illegal. We return an error and stop
            For instance, if we found a number followed by a letter. 
        */
        
        if (*str != ',' && *str != ' ' && *str != '\0') {
          fprintf(stderr, "[Error] Invalid set member - not an integer");
          return NULL;
        }

        /* If the number is negative or bigger than 127, the command is illegal. We return an error and stop */
        if (current_num < MIN_SET_VALUE || current_num > MAX_SET_VALUE) {
            fprintf(stderr, "[Error] Invalid set member - value out of range: %d\n", current_num);
            return NULL;
        }

        /* Find the next comma or end marker */
        while (*str != ',' && *str != '\0') {
            str++;
        }

        /* If the string ended without a -1, the command is illegal. We return an error and stop */
        if (*str == '\0' && !seen_ending) {
          fprintf(stderr, "[Error] List of set members is not terminated correctly\n");
          return NULL;
        }

        /* Check for double comma */
        if (*str == ',' && *(str + 1) == ',') {
            fprintf(stderr, "[Error] Multiple consecutive commas\n");
            return NULL;
        }

        /* Skip the comma */
        if (*str == ',') {
            str++;
        }
    }

    /* If -1 was seen, we check for junk values after it */
    if (seen_ending) {
        while (*str != '\0') {
            /* If there are any non-space characters after -1, the command is illegal. We return an error and stop */
            if (!isspace(*str)) {
                fprintf(stderr, "[Error] Extraneous text after end of command\n");
                return NULL;
            }
            str++;
        }

        /* Push a sentinal that will mark the end of the set (-1 can NOT naturally appear in the set) */
        set_members_size++;
        set_members = (int*) realloc(set_members, set_members_size * sizeof(unsigned int));

        /* If the allocation failed, we return an error and stop */
        if (!set_members) {
            fprintf(stderr, "[Error] couldn't allocate memory\n");
            exit(EXIT_FAILURE);
        }

        set_members[set_members_size - 1] = -1;

        /* Return the valid and complete numbers that should be added into the desired set. */
        return set_members;
    }


    return NULL;

}

/*
    retrieve_sets_indexes takes a string "str" and an array of valid sets "valid_sets".
    The function checks the syntax of the set names and enforces the restrictions of the set names structure.
    If the set names are valid, the function returns an array of the set indexes.
    If the set names are invalid, the function returns a NULL pointer.

    This function is used for commands that require 3 different sets (intersect_set, sub_set, symdiff_set, ...).
*/

int* retrieve_sets_indexes(char *str, const char *valid_sets[]) {

    int i = 0;

    int *setIndexes = (int*) malloc(SETS_PER_COMMAND * sizeof(int)); /* Array to store the future set indexes */

    /* If the allocation failed, we return an error and stop */
    if (!setIndexes) {
        fprintf(stderr, "[Error] couldn't allocate memory\n");
        exit(EXIT_FAILURE);
    }


    /* The process of finding each set repeats itself, so we use a loop. */

    for (; i < SETS_PER_COMMAND - 1; i++) {

        /* Skip any (valid) whitespaces until the next significant character */
        skip_spaces(&str);

        /* Check if the set name arguemnt is valid, and if so - get the index of the set in the valid_sets array */
        setIndexes[i] = is_valid_set(str, valid_sets, AMOUNT_OF_SETS);

        /* If setIndex is -1, the set name is not a valid one, we return an error and stop */
        if (setIndexes[i] == INVALID_VALUE) {
            fprintf(stderr, "[Error] Undefined set name\n");
            free(setIndexes);
            return NULL;
        }

        /* Move the pointer past the set name for further analysis */
        str += strlen(valid_sets[setIndexes[i]]);

        /* Skip any (valid) whitespaces until the next significant character */
        skip_spaces(&str);

        /* If the pointer doesn't point to a comma, the command is illegal. We return an error and stop */
        if (*str != ',') {
            fprintf(stderr, "[Error] No comma after set name\n");
            free(setIndexes);
            return NULL;
        }

        /* Skip the comma */
        str++;
    }

    /* Skip any (valid) whitespaces until the next significant character */
    skip_spaces(&str);

    /* The final set requires special attention since we can't have a comma after it */

    setIndexes[SETS_PER_COMMAND - 1] = is_valid_set(str, valid_sets, AMOUNT_OF_SETS);

    /* If setIndex is -1, the set name is not a valid one, we return an error and stop */
    if (setIndexes[SETS_PER_COMMAND - 1] == INVALID_VALUE) {
        fprintf(stderr, "[Error] Undefined set name\n");
        free(setIndexes);
        return NULL;
    }

    /* Move the pointer past the set name for further analysis */
    str += strlen(valid_sets[setIndexes[SETS_PER_COMMAND - 1]]);

    /* Skip any (valid) whitespaces until the next significant character */
    skip_spaces(&str);

    /* Check there is nothing but spaces after the end (junk values) */
    while (*str != '\0') {
        if (!isspace(*str)) {
            fprintf(stderr, "[Error] Extraneous text after end of command\n");
            free(setIndexes);
            return NULL;
        }
        str++;
    }

    /* Return the valid and complete indexes of the desired sets. */
    return setIndexes;
}
