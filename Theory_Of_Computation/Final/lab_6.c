#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isValidFloatingNumber(char* string) {
  char* chPtr = string;

  while (*chPtr != '\0') {
    if (!isdigit(*chPtr)) {
      if (*chPtr != '.')
        return 0;
      
      if (*(chPtr + 1) == '\0')
        return 0;
    }

    chPtr++;
  }

  return true;
}

int main(int argc, char** argv) {
  char string[50];
  printf("Enter a string: ");
  scanf("%s", string);

  printf("%s: %s floating point number", string, isValidFloatingNumber(string) ? "valid" : "invalid");

  return 0;
}