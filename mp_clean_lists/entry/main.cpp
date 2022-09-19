#include "List.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <iterator>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

using namespace cs225;

int main() {
  List<int> list;
  for (int i = 1; i <= 90; i++) list.insertBack(i);
  std::cout << list << std::endl;
  list.reverseNth(18);//not working properly
  std::cout << list << std::endl;
  return 0;
}
