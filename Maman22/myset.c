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

int skip_spaces(char **str) {
    while (isspace(**str)) {
        (*str)++;
    }
    return 1;
}

int is_valid_command(char *str, const char *valid_commands[], int num_commands) {
    int i = 0;


    for (; i < num_commands; i++) {
        if (strncmp(str, valid_commands[i], strlen(valid_commands[i])) == 0) {
            return 1;
        }
    }

    return 0;
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


    if (!skip_spaces(&str)) {
      return NULL;
    }

    if (*str != ',') {
        printf("[Error] No comma after set name\n");
        return NULL;
    }

    str++;


    /* Loop for comma-separated numbers */
    while (*str != '\0') {

        if (!skip_spaces(&str)) {
          return NULL;
        }

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
          printf("[Error] List of set members is not erminated correctly\n");
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


int main(int argc, char *argv[]) {

    set SETA = {{0}, 0};
    set SETB = {{0}, 0};
    set SETC = {{0}, 0};
    set SETD = {{0}, 0};
    set SETE = {{0}, 0};
    set SETF = {{0}, 0};

    int setIndex;

    const char *valid_sets[] = {
        "SETA",
        "SETB",
        "SETC",
        "SETD",
        "SETE",
        "SETF"
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

    char* str;

    set* selectedSet;

    while (1) {

        printf("Please enter a command\n");

        str = read_line();

        if (str == NULL) {
            /* EOF */
            printf("[Error] Reached EOF\n");
            continue;
        }

        if (!skip_spaces(&str)) {
            printf("[Error] No command found\n");
            continue;
        }


        if (!is_valid_command(str, valid_commands, 7)) {
            printf("[Error] Undefined command name\n");
            continue;
        }


        if (strncmp(str, "read_set", strlen("read_set")) == 0) {

            str += strlen("read_set");

            if (!skip_spaces(&str)) {
                return 0;
            }

            setIndex = is_valid_set(str, valid_sets, 6);


            if (setIndex == -1) {
                printf("[Error] Undefined set name\n");
                return 0;
            } else if (setIndex == 0) {
              selectedSet = &SETA;
            }

            str += 4;

            int* setMembers = validate_read_set(str);

            if (setMembers != NULL) {
                int i = 0;
                read_set(selectedSet, setMembers);
            }

            free(setMembers);
        } else if (strncmp(str, "print_set", strlen("print_set")) == 0) {

            print_set(&SETA);
        }

    }
    return 0;
}
