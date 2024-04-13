#include "my_suffix.c"
#define STRING_LENGTH 127

int main(int argc, char **argv)
{
  char c;
  unsigned int total;
  char str[STRING_LENGTH];

  /* Get c char from user. */
  printf("Enter a char:");
  scanf("%c", &c);

  /* Clean the buffer */
  while (getchar() != '\n');

  /* Get the complete string from user. */
  printf("Enter your string: ");
  fgets(str, sizeof(str), stdin);

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
