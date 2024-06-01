#include <stdio.h>
#include <stdlib.h>


/*
  partialSUms function: this function recieves an array of integers and a number representing the array length. It returns a new array
  the follows the definition of a "sum array": each element of the original array is replaced by the total sum of element up to it.

  the function does NOT change the original array, as required.

*/


int* partialSums(int original[], int size)
{
  int* res; /* Pointer for the result array */
  int i;

  /* Dynamically allocate memory for the result array. */
  res = (int*) malloc(size * sizeof(int));

  if (res == NULL)
  {
    /* Allocation failed for some reason */
    exit(-1);
  }


  /* First element of the array is ALWAYS the same. */
  res[0] = original[0];

  i = 1;
  for (; i < size; i++)
  {
    /* Easy enough to see, in a "sum array" called a, a[i] - a[i - 1] = original[i]. */
    res[i] = res[i - 1] + original[i];
  }

  /* Return the appropriate pointer for the array we've created. */

  return res;
}
