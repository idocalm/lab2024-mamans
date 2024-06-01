#include "functions.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void read_set(set* s , int* values) {

  int i;
  int num;

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

      printf("-- Set size: %d\n", s -> size);

      printf("-- SET PRINTOUT --\n");

      for (; i < ARRAY_SIZE * BITS_PER_INT; i++)
      {

        if (set_contains(s, i)) {
          if (counter % ARRAY_SIZE == 0)
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
