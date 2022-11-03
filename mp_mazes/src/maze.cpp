/* Your code here! */
#include "maze.h"

SquareMaze::SquareMaze() {
    //can leave this empty
}

void SquareMaze::makeMaze(int width, int height) {
    //if object represents a maze already, clear all existing data
    if (!board.empty() || !solPath.empty()) {
        solPath.clear();
        for (unsigned i = 0; i < board.size(); i++) {
            board[i].clear();
        }
        board.clear();
    }
    for (int i = 0; i < height; i++) { //row is y_index
        std::vector<Tile> vec;
        for (int j = 0; j < width; j++) { //col is x_index
            Tile *t = new Tile();
            t->x_index = j;
            t->y_index = i;
            vec.push_back(*t);
        }
        board.push_back(vec);
    }

}

bool SquareMaze::canTravel(int x, int y, int dir) const {
    return true;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists) {

}

std::vector<int> SquareMaze::solveMaze() {
    return std::vector<int>();
}

PNG* SquareMaze::drawMaze() const {
    return NULL;
}

PNG* SquareMaze::drawMazeWithSolution() {
    return NULL;
}