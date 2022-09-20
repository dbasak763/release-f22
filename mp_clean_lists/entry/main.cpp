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
  List<int> list1;

  list1.insertBack(1);
  list1.insertBack(3);
  list1.insertBack(4);
  list1.insertBack(6);

  List<int> list2;

  list2.insertBack(2);
  list2.insertBack(4);
  list2.insertBack(7);

  list1.mergeWith(list2);

  std::cout << list1 << std::endl;
  std::cout << list2 << std::endl;
  return 0;
}
