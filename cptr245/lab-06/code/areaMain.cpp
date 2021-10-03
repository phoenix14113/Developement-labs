/*



*/
#include <cstring>
#include <iostream>
#include <stdlib.h>

#include "areaFunction.h"

int main(int argc, char *argv[]) {
char *s = std::getenv("QUERY_STRING");
if (s == nullptr || strlen(s) < 3 || s[0] != 's' || s[1] != '=') {
  std::cerr << "Usage: QUERY_STRING=\"s=N\" area" << std::endl;
  return 1;
}
s += 2; // advance the string pointer beyond "s=" to point to the number
  int side = std::stoi(s);
s += 5;
  std::string users_name = s;
  for(int i=0; i<users_name.size(); i++){
    if(users_name[i] == '+'){
      users_name[i] = ' ';
    }
  }
  int square = AreaOfSquare(side);
  double circle = areaOfCircleWithRadius(side);
  std::cout << "Content-type: text/html;\n\n"
               "<!doctype html>\n"
               "<html itemtype=\"http://schema.org/WebPage\" lang=\"en\">\n"
               "  <head><meta charset=\"UTF-8\">\n"
               "    <title>Area Calculator Results</title>\n"
               "  </head>\n"
               "  <body>\n"
               "    <p>Hello " << users_name << "!!!</p>\n"
               "    <p>The area of a square with sides of " << side << " units is " << square  << " units.</p>\n"
               "    <p>The area of a circle with radius of " << side  << " units is " << circle <<" units.</p>\n"
               "    <p><a href=\"/\">Home</a></p>\n"
               "  </body>\n"
               "</html>\n" << std::endl;

  return 0;
}
