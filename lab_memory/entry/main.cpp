/**
 * @file main.cpp
 * A simple program that allocates students to rooms.
 */

#include <algorithm>
#include <vector>
#include <iostream>
#include <utility>

#include "fileio.h"
#include "letter.h"
#include "room.h"
#include "allocator.h"

/**
 * Main routine.
 * Creates an Allocator object and allocates the students.
 */
int main()
{
    std::cout << std::endl;

    fileio::init();
    std::cout << "Hi" << std::endl;
    Allocator theAllocator("../students.txt", "../rooms.txt"); //seg fault occurs here
    std::cout << "Hi" << std::endl;
    theAllocator.allocate(); //Invalid write of size 8
    std::cout << "Hi" << std::endl;
    theAllocator.printRooms();
    std::cout << "Hi" << std::endl;
    fileio::halt();

    std::cout << "Hi" << std::endl;    
    return 0;
}
