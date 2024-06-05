#ifndef SET_H
#define SET_H

/*
    Our goal is to efficiently represent a set of integers in the range [0, .., 127].
    Taking account the fact that we can use a single bit to represent a number,
    we can use an array of 16 integers to represent all numbers in the range [0, .., 127],
    where each integer in the array represents 8 numbers.

    For example, if we wish to represent the number 127, we would set values[15] = 1,
    for the number 126, we would set values[15] = 2, and so on.

    In general, if we wish to represent the number x, we would set values[x / 8] = 2^(x % 8).

    and if we wish to represent the number 55, we would set values[6] = 1.

    The size field will represent the number of elements in the set.

*/


#define ARRAY_SIZE 16
#define BITS_PER_INT 8
#define AMOUNT_OF_COMMANDS 7
#define AMOUNT_OF_SETS 6
#define SETS_PER_COMMAND 3
#define MIN_SET_VALUE 0
#define MAX_SET_VALUE 127
#define INVALID_VALUE -1

struct Set {
  int values[ARRAY_SIZE];
  int size;
};

typedef struct Set set;

typedef void (*command)(char*, const char**, set**);

/* Function prototypes for command handlers */

void read_set(set* s, int* values);
void print_set(set* s);
void union_set(set* a, set* b, set* c);
void intersect_set(set* a, set* b, set* c);
void sub_set(set* a, set* b, set *c);
void symdiff_set(set* a, set* b, set* c);
void stop();

#endif
