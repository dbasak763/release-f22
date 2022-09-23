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

    for (int i = 1; i <= 1000; i++)
        list.insertBack(i);
    //std::cout << "Here" << std::endl;
    list.tripleRotate();
    std::cout << list << std::endl;
   
   return 0;
}
