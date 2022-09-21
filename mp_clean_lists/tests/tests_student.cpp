#include <catch2/catch_test_macros.hpp>
#include "tests_helper.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include "List.h"

using namespace cs225;

// THESE TESTS ARE NOT GRADED AND ARE FOR YOU ONLY

TEST_CASE("Hello World", "") {
    std::string hello = "Hello World!";

    REQUIRE( hello == "Hello World!" );
}

TEST_CASE("List::triplerotate simple3", "[weight=10][part=1][valgrind]") {
    List<int> list;

    for (int i = 1; i <= 7; i++)
        list.insertBack(i);

    list.tripleRotate();

    stringstream s1, s2;

    list.print(s1);

    REQUIRE("< 2 3 1 5 6 4 7 >" == s1.str());

    //string forward = "";


}

TEST_CASE("List::triplerotate simple4", "[weight=10][part=1][valgrind]") {
    List<int> list;

    for (int i = 1; i <= 101; i++)
        list.insertBack(i);
    list.insertFront(256);
    list.insertFront(257);
    list.tripleRotate();

    stringstream s1, s2;

    list.print(s1);

    REQUIRE(103 == list.size());

    //string forward = "";


}

TEST_CASE("List::triplerotate complex1", "[weight=10][part=1][valgrind]") {
    List<int> list;

    for (int i = 1; i <= 101; i++)
        list.insertBack(i);
    list.insertFront(256);
    list.insertFront(257);
    list.tripleRotate();

    list.insertFront(15);
    list.insertFront(23);

    stringstream s1, s2;

    list.print(s1);

    REQUIRE(105 == list.size());

    List<int>::ListIterator iter = list.begin();

    //std::cout << *iter++ << std::endl;
    REQUIRE(*iter++ == 23);
    //std::cout << *iter++ << std::endl;
    REQUIRE(*iter++ == 15);
    //std::cout << *iter++ << std::endl;
    REQUIRE(*iter++ == 256);

    //string forward = "";


}

TEST_CASE("List::triplerotate image", "[weight=10][part=1][valgrind]") {
    PNG in;         in.readFromFile("../tests/split.png");

    List<HSLAPixel> list;
    for (unsigned i = 0; i < in.width(); i++)
        for (unsigned j = 0; j < in.height(); j++)
        {
            if (i == 0 && j < 11) std::cout << in.getPixel(i, j) << std::endl;
            list.insertBack(in.getPixel(i, j));
        }
    
    list.tripleRotate();
    //std::cout << "Triple Rotated Image" << std::endl;
    List<HSLAPixel>::ListIterator iter = list.begin();


    
        for (int i = 1; i <= 11; i++) std::cout << *iter++ << std::endl;
        for (int i = 1; i <= 11; i++) std::cout << *--iter << std::endl;

    vector<HSLAPixel> im1vect(list.begin(), list.end());

    PNG out1(in.width(), in.height());
    unsigned x = 0;
    for (unsigned i = 0; i < im1vect.size(); i++) {
        unsigned y = i % in.height();
        out1.getPixel(x, y) = im1vect[i];
        if (y == (in.height() - 1)) { x++; }
    }
    out1.writeToFile("tripleRotated_1.png");
    
    for (int i = 1; i <= 3; i++) list.tripleRotate();


    vector<HSLAPixel> im2vect(list.begin(), list.end());

    PNG out2(in.width(), in.height());
    x = 0;
    for (unsigned i = 0; i < im2vect.size(); i++) {
        unsigned y = i % in.height();
        out2.getPixel(x, y) = im2vect[i];
        if (y == (in.height() - 1)) { x++; }
    }
    out2.writeToFile("tripleRotated_2.png");

    REQUIRE(out1 == out2);

    //stringstream s1, s2;

    //list.print(s1);

    SUCCEED("Didn't crash!");

    
}

TEST_CASE("List::reverseNth Size", "[weight=5][part=2]") {
  PNG in;        in.readFromFile("../tests/alma.png");
  PNG expected;  expected.readFromFile("../tests/expected-reverseN_1.png");

  List<HSLAPixel> list = imageToList(in);

  int size1 = list.size();

  list.reverseNth(in.height() * 20);

  int size2 = list.size();

  PNG out = listToImage(list, in.width(), in.height());
  out.writeToFile("actual-reverseN_1.png");
  INFO("Output image `out` saved as actual-reverseN_1.png");

  REQUIRE(size1 == size2);
  //REQUIRE( out == expected );
}

TEST_CASE("List::reverseNth Contents", "[weight=5][part=2]") {
  PNG in;        in.readFromFile("../tests/alma.png");
  PNG expected;  expected.readFromFile("../tests/expected-reverseN_1.png");

  List<HSLAPixel> list = imageToList(in);
  List<HSLAPixel> list2 = imageToList(in);

  list2.reverseNth(in.height() * 20);

  List<HSLAPixel>::iterator *it1 = list.end();
  List<HSLAPixel>::iterator *it2 = list2.end();

  for ()

  /*
  PNG out = listToImage(list, in.width(), in.height());
  out.writeToFile("actual-reverseN_1.png");
  INFO("Output image `out` saved as actual-reverseN_1.png");
  */
  
  std::cout << res_string << std::endl;
  REQUIRE(s1.str() == s2.str());
  //REQUIRE( out == expected );
}
