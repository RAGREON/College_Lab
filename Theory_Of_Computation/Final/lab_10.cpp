#include <iostream>
#include <unordered_map>
#include <functional>

/*
  half the size -> l = n / 2
  total iteration: l + (l * l)
*/

int main(int argc, char** argv) {
  std::string input;
  
  std::cout << "enter string: ";
  std::cin >> input;

  char* currentChar = &input[0];

  std::unordered_map<int, std::function<int(char**)>> state_map;

  state_map[0] = [](char** ch) {
    if (**ch == 'a') {
      *(*ch)++ = 'x';
      return 1;
    }

    return (**ch == 'y') ? 3 : -1;
  };

  state_map[1] = [](char** ch) {
    if (**ch == 'b') {
      *(*ch)-- = 'y';
      return 2;
    }

    if (**ch == 'a' || **ch =='b' || **ch == 'y') {
      *(*ch)++;
      return 1;
    }

    return -1;
  };

  state_map[2] = [](char** ch) {
    if (**ch == 'x') {
      (*ch)++;
      return 0;
    }

    if (**ch == 'a' || **ch == 'b' || **ch == 'y') {
      (*ch)--;
      return 2;
    } 
    return -1;
  };

  state_map[3] = [](char** ch) {
    if (**ch == '\0') return 4;

    if (**ch == 'y') {
      (*ch)++;
      return 3;
    }

    return -1;
  };

  int maxIteration = input.length() + input.length() * input.length();
  int currentItr = 0;

  int state = 0;
  while (currentItr++ < maxIteration) { 
    state = state_map[state](&currentChar);

    if (state == 4 || state == -1) break;
  }

  std::cout << "current iteration: " << currentItr << "\n";
  std::cout << ((state == 4) ? "valid" : "invalid") << "\n";

  return 0;
}