#include <stdio.h>
#define BYTES 8

/*
print_in_binary function: this function receives an unsigned number and prints it in binary base.
The algorithm uses a simple for loop to go through each bit in the system and print the matching digit in binary.

*/

void print_in_binary(unsigned int number)
{
  /* Loop through all bits in the system. */
  int bits;
  for (bits = sizeof(unsigned int) * BYTES - 1; bits >= 0; bits--)
  {
    /* Get the matching digit and print it */
    printf("%d", number >> bits & 1);
  }


}

/*
  my_add function: this function receives 2 unsigned integers and returns the addition of them.
  WE ASSUME THAT BOTH NUMBERS ARE POSITIVE (HENCE, UNSIGNED).
  The algorithm uses a while loop to iterate as long as we're not finished with the bits addition.
  Each iteration we calculate the "sum" of the 2 most-right bits, and then we figure the carry for the next iteration.

  The operation is finished once b is 0, which means a now has the value of a+b.

*/


unsigned int my_add(unsigned int a, unsigned int b)
{
  unsigned int carry = 0; /* The value that needs to be carried each addition. */
  unsigned int sum = 0; /* For calculating in-loop sum */  

  /* Print arguments a and b in binary base */
  printf("Binary a: ");
  print_in_binary(a);
  printf("\n");

  printf("Binary b: ");
  print_in_binary(b);
  printf("\n");


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
