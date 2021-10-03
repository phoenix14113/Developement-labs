
#include <iostream>
#include <ostream>

#include "areaFunction.h"

int main() {
  int test1 = 2;
  int areatest1 = AreaOfSquare(test1);
  if (areatest1 == 4) {
    std::cout << "Passed square area" << std::endl;
  } else {
    std::cerr << "Failed square area" << std::endl;
    return 1;
  }
  double areatest2 = areaOfCircleWithRadius(test1);
  if (areatest2 == test1 * test1 * 3.14) {
    std::cout << "Passed circle area" << std::endl;
  } else {
    std::cerr << "Failed circle area" << std::endl;
    return 1;
  }
  return 0;
}
