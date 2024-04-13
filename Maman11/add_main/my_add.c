#include <stdio.h>
#define BYTES 8 
void print_in_binary(unsigned int number)
{
  /* Loop through all bits in the system. */
  int bits;
  for (bits = sizeof(unsigned int) * BYTES - 1; bits >= 0; bits--)
  {
    /* Get the matching digit and print it */
    printf("%d", number >> bits & 1);
  }

  printf("\n");

}

unsigned int my_add(unsigned int a, unsigned int b)
{
  unsigned int carry = 0;
  unsigned int sum = 0;

  /* Print arguments a and b in binary base */
  printf("Binary a: ");
  print_in_binary(a);

  printf("Binary b: ");
  print_in_binary(b);


  while (b != 0)
  {
    /* Calculate the sum using XOR, without accounting the carry */
    sum = a ^ b;

    /* Finding out the carry and shifting it 1 bit to the left */
    carry = (a & b) << 1;

    /* Updating values accordingly for the next loop run */
    a = sum;
    b = carry;

  }

  /* Print the result in binary base */
  printf("Binary result: ");
  print_in_binary(a);

  return a;

}
