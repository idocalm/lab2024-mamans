#include "my_add.c"


/*

  This program is designed to ask the user for 2 numbers a and b
  Then, it would perform binary addition between a and b, print the result in binary base
  Finally, it will print the addition result in the normal decimal base as well.

  Performing the addition is being done by using the my_add() function from my_add.c, that uses bitwise operations.

*/

int main(int argc, char **argv)
{
  unsigned int a; /* First number */
  unsigned int b; /* Second number */
  unsigned int res; /* Result number */ 

  /* Get a and b from user. */
  printf("Enter first and second numbers (a) (b):");
  scanf("%u %u", &a, &b);

  /* Print the values received. */
  printf("\nFirst number: %u \nSecond number: %u \n", a, b);

  res = my_add(a, b);

  /* Print the results in base 10. */
  printf("\nmy_add(a,b) with decimals a = %u, b = %u\n", a, b);
  printf("Decimal result: %u\n", res);

  return 0;
}
