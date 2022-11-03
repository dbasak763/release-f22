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
        vec.clear();
    }
    width_ = width;
    height_ = height;

    //need to add randomly deleting walls part such that no cycle appears in our graph(we have a tree), until no more edges can be deleted

}
//assume (x, y) is a valid tile location
bool SquareMaze::canTravel(int x, int y, int dir) const {
    Tile t = board[y][x];
    if (dir == 0) { //right
        if (x == (width_ - 1)) return false; //out of bounce
        return (t.wall_dir[0] == 0); //no wall present, so can traverse
    } else if (dir == 1) { //down
        if (y == (height_ - 1)) return false; //out of bounce
        return (t.wall_dir[1] == 0); //no wall present, so can traverse
    } else if (dir == 2) { //left
        if (x == 0) return false; //out of bounce
        return (t.wall_dir[2] == 0); //no wall present, so can traverse
    } else { //up
        if (y == 0) return false; //out of bounce
        return (t.wall_dir[3] == 0); //no wall present, so can traverse
    }

}

void SquareMaze::setWall(int x, int y, int dir, bool exists) {
    Tile t = board[y][x];
    if(exists) {
        t.wall_dir[dir] = 1;
    } else {
        t.wall_dir[dir] = 0;
    }
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