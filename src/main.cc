#include <iostream>

#include "../include/computer_club.h"

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
    return 1;
  }

  ComputerClub club;
  club.readFromFile(argv[1]);
  club.printData();
  return 0;
}
