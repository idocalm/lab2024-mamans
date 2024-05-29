#include "set.h"
#include <stdlib.h>
#include <stdio.h>



int main(int argc, char *argv[]) {

  set SETA = {{0}, 2};
  set SETB = {{0}, 2};
  set SETC = {{0}, 2};

  int arr[4] = {25, 15, 100,-1};
  int arr2[4] = {15, 75, 125, -1};

  read_set(&SETA, arr);
  read_set(&SETB, arr2);

  union_set(&SETA, &SETB, &SETC);

  print_set(&SETC);



  return 0;
}
