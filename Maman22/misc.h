
#ifndef MISC_H
#define MISC_H

/* Function prototypes for command handlers */

void skip_spaces(char **str);
int is_valid_set(char *str, const char *valid_sets[], int num_sets);
int* retrieve_set_members(char *str);
int* retrieve_sets_indexes(char *str, const char *valid_sets[]);

#endif
