#include "set.h"
#include <stdio.h>

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
