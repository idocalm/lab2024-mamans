#include "set.h"
#include <stdlib.h>
#include <stdio.h>



int main(int argc, char *argv[]) {

  set SETA = {{0}, 2};
  int arr[4] = {25, 15, 100,-1};

  read_set(&SETA, arr);

  print_set(&SETA);
  return 0;
}
