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
   
   for (int i = 1; i <= 10; i++) list.insertFront(i);

   std::cout << list << std::endl;

   list.tripleRotate();

   std::cout << list << std::endl;

   List<unsigned>::ListIterator iter = list.end();
   --iter;
   std::cout << *iter << std::endl;
   std::cout << "New Line" << std::endl;
   for (int i = 1; i <= 10; i++) {
      //std::cout << "i = " << i << std::endl;
      std::cout << *iter--;
   }
   std::cout << std::endl;
   return 0;
}
