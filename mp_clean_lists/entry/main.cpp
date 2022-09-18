#include "List.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "tests/tests_helper.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

using namespace cs225;

int main() {
  PNG in;        in.readFromFile("../tests/alma.png");
  PNG expected;  expected.readFromFile("../tests/expected-reverseN_1.png");

  List<HSLAPixel> list = imageToList(in);
  list.reverseNth(in.height() * 20);

  PNG out = listToImage(list, in.width(), in.height());
  out.writeToFile("actual-reverseN_1.png");

  return 0;
}
