#include "List.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>


int main() {
    List<int> list;

    list.insertBack(1);
    list.insertBack(2);
    list.insertBack(3);
    list.insertBack(4);

    std::cout << list << std::endl;

    List<int> slist = list.split(2); //seg fault, not working properly

    std::cout << list << std::endl;
    std::cout << slist << std::endl;

    return 0;
}
