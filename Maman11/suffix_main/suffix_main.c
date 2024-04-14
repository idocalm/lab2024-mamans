#include "my_suffix.c"
#define STRING_LENGTH 127


/*

  This program is designed to ask the user for a letter b and a whole string
  Then, it would print every suffix of the string that starts with the letter b.
  Finally, it prints the total amount of suffixes that were printed and detected.

  Performing the print is being done by using the suffix() function from my_suffix.c.

*/


/* main function (receieves inputs and does as described above). */
int main(int argc, char **argv)
{

  char c; /* a letter that would be entered by the user. */
  unsigned int total; /* the total future suffixes. */
  char str[STRING_LENGTH]; /* a string that would be entered by the user. */

  /* Get c char from user. */
  printf("Enter a char:");
  scanf("%c", &c);

  /* Clean the buffer */
  while (getchar() != '\n');

  /* Get the complete string from user. */
  printf("Enter your string: ");
  fgets(str, sizeof(str), stdin);

  /* */
  if (strlen(str) == 0)
  {
    printf("DSADSADADASDAD");
    str[0] = '\0';
  }

  /* Handle the \n case if exists */
  if (str[strlen(str) - 1] == '\n')
  {
      str[strlen(str) - 1] = '\0';
  }

  /* Print the values received. */
  printf("\nReceived char: %c \nand str: ", c);

  puts(str);
  printf("\n--------- SUFFIXES --------- \n");

  total = suffix(str, c);

  printf("\n-------------------- \n");

  /* Print the total amount of suffixes that exist. */
  printf("\nsuffix(str,c) with str = %s, c = %c\n", str, c);
  printf("Found: %u suffixes \n", total);

  return 0;
}
