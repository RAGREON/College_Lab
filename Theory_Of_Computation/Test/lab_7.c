// Check whether the email address is valid or not

#include <stdio.h>
#include <string.h>
#include <ctype.h>

// username + @ + domain + . + type

int countChar(char* string, char ch) {
  int count = 0;
  char* chPtr = string;

  while ((chPtr = strchr(chPtr, ch)) != NULL) {
    count++;
    chPtr++;
  }

  return count;
}

int isValidChar(char ch) {
  return (isalpha(ch) || isdigit(ch) || ch == '_');
}

int isValidSubstring(char* string, int checkDot) {
  if (strlen(string) <= 0 || string[0] == '.') return 0;

  char* chPtr = string;
  int dotEncountered = 0;
  int postLength = 0, preLength = 0;
  int previousDot = 0;

  if (!checkDot) {
    dotEncountered = 1;
    preLength = 1;
  }

  int offset = 0;

  while (*chPtr != '\0') {
    if (*chPtr == '@') goto return_block;
    
    if (*chPtr == '.') {
      if (!dotEncountered) dotEncountered = 1;
      if (previousDot) return 0;

      previousDot = 1;
      
      goto skip;
    }
    else if (!isValidChar(*chPtr)) return 0;

    if (dotEncountered) postLength++;
    else preLength++;

    previousDot = 0;

skip: 

    chPtr++;
    offset++;
  }

return_block:

  if (!dotEncountered || postLength == 0 || preLength == 0 || *(chPtr - 1) == '.') return 0;

  return offset;
}


int isValidEmail(char* string) {
  if (countChar(string, '@') != 1 || string[0] == '@' || string[strlen(string) - 1] == '@') return 0;

  int offset = isValidSubstring(string, 0);

  printf("%d\n", offset);

  if (isValidSubstring(string + offset + 1, 1) != 0)
    return 1;

  return 0;
}


int main(int argc, char** argv) {
  char string[50];
  printf("enter string: ");
  scanf("%s", string);

  printf("%s: %s\n", string, isValidEmail(string) ? "valid": "invalid");

  return 0;
}