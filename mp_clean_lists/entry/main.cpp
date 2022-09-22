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
   List<char> list;
   for (int i = 1; i <= 100; i++) {
      list.insertBack(i);
   }

   list.tripleRotate();

   std::cout << list << std::endl;
   
   List<char>::ListIterator iter = list.begin();
   for (int i = 1; i <= 100; i++) {
      std::cout << *++iter << std::endl;
   }

   List<char>::ListIterator iter = list.end();
   for (int i = 1; i <= 100; i++) {
      std::cout << *--iter << std::endl;
   }
   
   return 0;
}
