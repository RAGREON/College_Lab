#include <stdio.h>
#include <string.h>
#include <ctype.h>

int validFloatingNumber(char* string) {
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

void testCases(char** args, int size) {
  for (int i = 1; i < size; i++) {
    char* string = args[i];

    printf("%s: ", string);
    if (validFloatingNumber(string)) {
      printf("valid floating point number\n");
    }
    else {
      printf("invalid floating point number\n");
    }
  } 
}

int main(int argc, char** argv) {
  testCases(argv, argc);

  return 0;
}