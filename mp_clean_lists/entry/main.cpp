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
   List<unsigned> list;
   list.insertFront(1);
   list.insertFront(2);
   list.insertFront(3);

   std::cout << list << std::endl;

   List<unsigned>::ListIterator iter = list.begin();
   iter++;
   iter++;
   iter++;
   std::cout << "Hello" << std::endl;
   //std::cout << *iter << std::endl;
   //std::cout << *iter << std::endl;
   std::cout << *(--iter) << std::endl;
   return 0;
}
