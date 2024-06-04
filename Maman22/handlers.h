#ifndef HANDLERS_H
#define HANDLERS_H

#include "misc.h"
#include "set.h"


/* Function prototypes for command handlers */
void read_set_handler(char *str, const char **valid_sets, set **sets);
void print_set_handler(char *str, const char **valid_sets, set **sets);
void union_set_handler(char *str, const char **valid_sets, set **sets);
void intersect_set_handler(char *str, const char **valid_sets, set **sets);
void sub_set_handler(char *str, const char **valid_sets, set **sets);
void symdiff_set_handler(char *str, const char **valid_sets, set **sets);
void stop_handler(char *str);

#endif
