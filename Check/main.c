#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



int main() {

  char str[] = " -1 50";

  printf("%d\n", isdigit(*str));

  return 0;
}
