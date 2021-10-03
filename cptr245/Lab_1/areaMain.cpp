/*



*/
#include <iostream>

#include "areaFunction.h"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: 'area N' where area is an integer" << std::endl;
    return 1;
  }
  char *s = argv[1];
  int side = std::stoi(s);
  int square = AreaOfSquare(side);
  std::cout << "The area of a square with sides " << side << " units long is "
            << square << " units squared." << std::endl;

  double circle = areaOfCircleWithRadius(side);
  std::cout << "The area of a circle with sides " << side << " units long is "
            << circle << " units squared." << std::endl;

  return 0;
}
