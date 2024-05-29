#include "set.h"
#include <stdio.h>


void set_insert(set* s, int num) {

  int index;
  int position;


  index = num / BITS_PER_INT;
  position = num % BITS_PER_INT;

  s -> values[index] |= (1 << position);
  s ->size++;
}

void set_remove(set* s, int num) {

  int index;
  int position;

  index = num / BITS_PER_INT;
  position = num % BITS_PER_INT;

  s ->values[index] &= ~(1 << position);
  s ->size--;
}


int set_contains(set* s, int num) {
  int index;
  int position;
  int mask;

  index = num / BITS_PER_INT;
  position = num % BITS_PER_INT;

  mask = 1 << position;

  return s ->values[index] & mask;
}
