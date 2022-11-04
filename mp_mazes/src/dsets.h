/* Your code here! */
#pragma once

#include <stdint.h>
#include <vector>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

using namespace cs225;

//using namespace std;

class DisjointSets {


    private:
        std::vector<int> par;

    public:
        void addelements(int num);
        int find(int elem);
        void setunion(int a, int b);
        int size(int elem);
        void print();

};