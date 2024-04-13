#include "my_add.c"

int main(int argc, char **argv)
{
  unsigned int a;
  unsigned int b;
  unsigned int res;

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
