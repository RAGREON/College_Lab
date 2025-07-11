// C-Program to check whether a string is a valid floating point number

#include <stdio.h>
#include <ctype.h>

int isValidFloatingNumber(char* string) {
  char* chPtr = string;

  while (*chPtr != '\0') {
    if (!isdigit(*chPtr)) {
      // checks if the non-digit character is '.'
      // returns false if char != '.'

      if (*chPtr != '.')
        return 0;

      // if there isn't any digit after '.' return false
      if (*(chPtr + 1) == '\0')
        return 0;
    }

    chPtr++;
  }

  return true;
}

int main(int argc, char** argv) {
  // input string
  char string[50];
  printf("Enter a string: ");
  scanf("%s", string);

  // checks if string is a valid floating point number or not
  printf("%s: %s floating point number", string, isValidFloatingNumber(string) ? "valid" : "invalid");

  return 0;
}