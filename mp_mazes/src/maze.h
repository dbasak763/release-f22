/* Your code here! */
#pragma once

#include <stdint.h>
#include <vector>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

using namespace cs225;

//using namespace std;

class SquareMaze {


    private:


    public:
        SquareMaze();
        void makeMaze(int width, int height);
        bool canTravel(int x, int y, int dir) const;
        void setWall(int x, int y, int dir, bool exists);
        std::vector<int> solveMaze();
        PNG* drawMaze() const;
        PNG* drawMazeWithSolution();

};