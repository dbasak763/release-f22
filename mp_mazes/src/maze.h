/* Your code here! */
#pragma once

#include <stdint.h>
#include <vector>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "dsets.h"

using namespace cs225;

struct Tile {
    int x_index, y_index; //point
    int wall_dir[2] = {1, 1}; //right and bottom
    //std::vector<int> walls = {0, 1, 2, 3};
    // dir = 0 represents a rightward step (+1 to the x coordinate)
    // dir = 1 represents a downward step (+1 to the y coordinate)
    // dir = 2 represents a leftward step (-1 to the x coordinate)
    // dir = 3 represents an upward step (-1 to the y coordinate)
    //walls(could be located) on each side
};

//using namespace std;
//Each SquareMaze object represents a randomly-generated square maze and its solution.
class SquareMaze {


    private:
        std::vector<std::vector<Tile>> board; //a 2D - representation of the board (of square maze)
        std::vector<Tile> solPath; //starts at tile(0, 0) , ends at a bottom-most tile of board
        //std::vector<std::vector<int>> wallsAtTiles_;
        int width_;
        int height_;
        DisjointSets d;
        void deleteWall(int x, int y, int dir);
        bool outofBounce(int x, int y, int dir);
    public:
        SquareMaze();
        void makeMaze(int width, int height);
        bool canTravel(int x, int y, int dir) const;
        void setWall(int x, int y, int dir, bool exists);
        std::vector<int> solveMaze();
        PNG* drawMaze() const;
        PNG* drawMazeWithSolution();

};