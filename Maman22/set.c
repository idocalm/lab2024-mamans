#include "set.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
  set_insert takes an integer "num" and a pointer to a set, inserts the integer
   to the set values and adjusts the set size.
*/
void set_insert(set* s, int num) {

  int index;
  int position;


  index = num / BITS_PER_INT;
  position = num % BITS_PER_INT;

  s -> values[index] |= (1 << position);
  s ->size++;
}

/*
  set_remove takes an integer "num" and a pointer to a set, removes the integer
   from the set values and adjusts the set size.
*/

void set_remove(set* s, int num) {

  int index;
  int position;

  index = num / BITS_PER_INT;
  position = num % BITS_PER_INT;

  s ->values[index] &= ~(1 << position);
  s ->size--;
}

/*
  set_contains takes an integer "num" and a pointer to a set, and returns whether the number apears in the set values.
*/


int set_contains(set* s, int num) {
  int index;
  int position;
  int mask;

  index = num / BITS_PER_INT;
  position = num % BITS_PER_INT;

  mask = 1 << position;

  return s ->values[index] & mask;
}

/*
  count_bits takes a number and counts the amount of bits in it.
  This is primarily used to recount the amount of numbers a set stores
*/

int count_bits(int num) {
    int count = 0;
    while (num) {
        count += num & 1;
        num >>= 1;
    }
    return count;
}


/*
  read_set takes a pointer to a set and an array of integers, and sets the set to contain the integers in the array.
  The function also adjusts the set size.
*/

void read_set(set* s , int* values) {

    int i;

    i = 0;

    for (; i < ARRAY_SIZE; i++) {
        s -> values[i] = 0;
    }

    s -> size = 0;

    i = 0;

    while (values[i] != -1) {
      set_insert(s, values[i]);
      i++;
    }

}

/*
  print_set takes a pointer to a set and prints the set values in ascending order.
*/

void print_set(set* s) {

  int i;
  int counter;

  if (s -> size == 0) {
      printf("The set is empty.\n");
  } else {
      i = 0;

      printf("--[SET]--\n");

      for (; i < ARRAY_SIZE * BITS_PER_INT; i++)
      {

        if (set_contains(s, i)) {
          /* Print a new line every 16 numbers */
          if (counter % ARRAY_SIZE == 0 && counter != 0)
          {
            printf("\n");
          }
          counter++;
          printf("%d ", i);
        }
      }

      printf("\n--[SET]--\n");

  }
}

/*
  union_set takes 3 pointers to sets, and performs a union of the first two sets, storing the result in the third set.
*/

void union_set(set* a, set* b, set* c) {
    int i;

    i = 0;

    /* Perform a bitwise OR operation on the values of the two sets */
    for (; i < ARRAY_SIZE; i++)
    {
        c -> values[i] = a -> values[i] | b -> values[i];
    }

    c -> size = 0;
    i = 0;

    /* Count the amount of numbers in the new set */
    for (; i < ARRAY_SIZE; i++)
    {
        c -> size += count_bits(c -> values[i]);
    }

}

/*
  intersect_set takes 3 pointers to sets, and performs an intersection of the first two sets, storing the result in the third set.
*/

void intersect_set(set* a, set* b, set* c) {
    int i;

    i = 0;

    /* Perform a bitwise AND operation on the values of the two sets */
    for (; i < ARRAY_SIZE; i++)
    {
        c -> values[i] = a -> values[i] & b -> values[i];
    }

    c -> size = 0;
    i = 0;

    /* Count the amount of numbers in the new set */
    for (; i < ARRAY_SIZE; i++)
    {
        c -> size += count_bits(c -> values[i]);
    }
}

/*
  sub_set takes 3 pointers to sets, and performs a subtraction of the second set from the first set, storing the result in the third set.
*/

void sub_set(set* a, set* b, set* c) {
    int i;

    i = 0;

    /* Perform a bitwise AND operation on the values of the two sets, and then negate the result */
    for (; i < ARRAY_SIZE; i++)
    {
        c -> values[i] = a -> values[i] & ~(b -> values[i]);
    }

    c -> size = 0;
    i = 0;

    /* Count the amount of numbers in the new set */
    for (; i < ARRAY_SIZE; i++)
    {
        c -> size += count_bits(c -> values[i]);
    }
}

/*
  symdiff_set takes 3 pointers to sets, and performs a symmetric difference of the first two sets, storing the result in the third set.
*/

void symdiff_set(set* a, set* b, set* c) {
    int i;

    i = 0;

    /* Perform a bitwise XOR operation on the values of the two sets */
    for (; i < ARRAY_SIZE; i++)
    {
        c -> values[i] = a -> values[i] ^ b -> values[i];
    }

    c -> size = 0;
    i = 0;
    
    /* Count the amount of numbers in the new set */
    for (; i < ARRAY_SIZE; i++)
    {
        c -> size += count_bits(c -> values[i]);
    }
}

/*
  stop is a function that stops the program.
*/

void stop() {
    printf("Program terminated\n");
    exit(0);
}
