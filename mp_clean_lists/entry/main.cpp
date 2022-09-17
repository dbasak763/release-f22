#include "List.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>


int main() {
    List<int> list;

    for (int i = 1; i <= 14; i++)
        list.insertBack(i);
        
    std::cout << list << std::endl;

    list.tripleRotate();


    std::cout << list << std::endl;

    return 0;
}
