#include <string.h>
#include <stdio.h>

/*
  suffix function: receives a string (str) and a character (c), prints the suffixes of str that start with c,
  and returns the total suffixes that were printed.

  Algorithm uses a simple for loop to go through every letter in the string, and check if it is the same as c.
  If so, we simply use the printf function to print the string all the way from the letter to the end, and add 1 to our counter.

  After looping through the whole string we return the total amount.
*/

int suffix(char str[], char c)
{
  unsigned int total = 0; /* Used to count how many suffixes exist. */

  unsigned int length = strlen(str); /* Used to store the length of the string. */
  int i = 0;

  /* Loop through each char in the string */
  for (; i< length; i++)
  {
    if (str[i] == c)
    {
      /* If the char is what we're looking for - print the suffix */
      printf("%s\n", &str[i]);
      total++;
    }
  }

  /* Return the total amount of suffixes we found */

  return total;

}
