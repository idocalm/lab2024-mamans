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

/*
    Declarations of function that will be implemented in set.c
*/

/* read_set takes in a set and an array of numbers and sets the set to be the numbers in it */
void read_set(set* s, int* values);

/* print_set prints the elements of the set in ascending order */
void print_set(set* s);

/* union_set takes in 3 sets, performs a union of set a with set b, and stores the result in set c */
void union_set(set* a, set* b, set* c);

/* intersect_set takes in 3 sets, performs an intersection of set a with set b, and stores the result in set c */
void intersect_set(set* a, set* b, set* c);

/* sub_set takes in 3 sets, performs a subtraction of set a with set b, and stores the result in set c */
void sub_set(set* a, set* b, set *c);

/* symdiff_set takes in 3 sets, and performs symmetric difference of set a with set b, and stores the result in set c  */
void symdiff_set(set* a, set* b, set* c);

/* stop takes no operands and stops the program */
void stop();

#endif
