#include "my_add.c"

int main(int argc, char **argv)
{
  unsigned int a;
  unsigned int b;
  unsigned int res;

  printf("Enter first and second numbers (a) (b):");
  scanf("%u %u", &a, &b);

  printf("\nFirst number: %u \nSecond number: %u \n", a, b);

  res = my_add(a, b);

  printf("\nmy_add(a,b) with decimals a = %u, b = %u\n", a, b);
  printf("Decimal result: %u\n", res);

  return 0;
}
