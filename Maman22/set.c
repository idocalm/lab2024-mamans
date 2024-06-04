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



void read_set(set* s , int* values) {

  int i;

  i = 0;

  for (; i < ARRAY_SIZE; i++)
  {
    s -> values[i] = 0;
  }

  s -> size = 0;

  i = 0;

  while (values[i] != -1) {
    set_insert(s, values[i]);
    i++;
  }

}

void print_set(set* s) {

  int i;
  int counter;

  if (s -> size == 0) {
      printf("The set is empty.\n");
  } else {
      i = 0;


      printf("-- SET PRINTOUT --\n");

      for (; i < ARRAY_SIZE * BITS_PER_INT; i++)
      {

        if (set_contains(s, i)) {
          if (counter % ARRAY_SIZE == 0 && counter != 0)
          {
            printf("\n");
          }
          counter++;
          printf("%d ", i);
        }
      }

      printf("\n-- END OF PRINTOUT --\n");

  }
}

void union_set(set* a, set* b, set* c) {
    int i;

    i = 0;

    for (; i < ARRAY_SIZE; i++)
    {
        c -> values[i] = a -> values[i] | b -> values[i];
    }

    c -> size = 0;
    i = 0;
    for (; i < ARRAY_SIZE; i++)
    {
        c -> size += count_bits(c -> values[i]);
    }
}

void intersect_set(set* a, set* b, set* c) {
    int i;

    i = 0;

    for (; i < ARRAY_SIZE; i++)
    {
        c -> values[i] = a -> values[i] & b -> values[i];
    }

    c -> size = 0;
    i = 0;
    for (; i < ARRAY_SIZE; i++)
    {
        c -> size += count_bits(c -> values[i]);
    }
}

void sub_set(set* a, set* b, set* c) {
    int i;

    i = 0;

    for (; i < ARRAY_SIZE; i++)
    {
        c -> values[i] = a -> values[i] & ~(b -> values[i]);
    }

    c -> size = 0;
    i = 0;
    for (; i < ARRAY_SIZE; i++)
    {
        c -> size += count_bits(c -> values[i]);
    }
}

void symdiff_set(set* a, set* b, set* c) {
    int i;

    i = 0;

    for (; i < ARRAY_SIZE; i++)
    {
        c -> values[i] = a -> values[i] ^ b -> values[i];
    }

    c -> size = 0;
    i = 0;
    for (; i < ARRAY_SIZE; i++)
    {
        c -> size += count_bits(c -> values[i]);
    }
}

void stop() {
    printf("Program terminated \n");
    exit(0);
}
