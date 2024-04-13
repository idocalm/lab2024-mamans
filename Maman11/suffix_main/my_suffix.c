#include <string.h>
#include <stdio.h>

int suffix(char str[], char c)
{
  unsigned int total = 0; /* Used to count how many suffixes exist. */

  unsigned int length = strlen(str);/* Used to store the length of the string. */
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
