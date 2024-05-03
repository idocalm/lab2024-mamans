#include "partialSums.c"

/*

  This program is designed to ask the user for a number representing a length of an array, and then asks the
  user to input each element in the array.
  Then, it would calculate the "sum array", uning the function partialSums written in partialSums.c.
  Finally, it will print the result array in a nice pattern.

  A note: all calculations, array inputs and outputs are designed in DECIMAL BASE.

*/


int main()
{
  int size; /* Used to store the user's array length */
  int i;
  int* result; /* A pointer for the result array */
  int* arr; /* A pointer for the received array */  

  /* Ask the user for the array length */
  printf("Enter the desired size of array: ");
  scanf("%d", &size);

  /* ALlocate the needed memory dynamically */
  arr = (int*) malloc(size * sizeof(int));

  /* Ask the user for each element in the array separately */
  printf("Enter each element in the array: \n");

  i = 0;
  for (; i < size; i++)
  {
    scanf("%d", &arr[i]);
  }

  /* Re-print the information we received */
  printf("Size received is: %d\n", size);
  printf("Array received is : [ ");
  i = 0;
  for (; i < size; i++)
  {
    printf("%d ", arr[i]);
  }
  printf("]\n");

  /* Use the partialSums function to get the result array pointer */

  result = partialSums(arr, size);

  printf("--------------\n");


  /* Print each element of the result array */
  printf ("Result received is: [ ");

  i = 0;
  for (; i < size; i++)
  {
    printf("%d ", result[i]);
  }

  printf("]\n");

  /* Make sure we free the memory after the complete process is done and finished */
  free(arr);
  free(result);

  return 0;

}
