/* Your code here! */
#include "maze.h"

SquareMaze::SquareMaze() {
    //can leave this empty
}
//assume that tile in direction can be traveled
void SquareMaze::deleteTile(int x, int y, int dir) {
    Tile t = board[y][x];
    t.wall_dir[dir] = 0;
    if (dir == 0) {
        board[y][x + 1].wall_dir[2] = 0;
    } else if (dir == 1) {
        board[y + 1][x].wall_dir[3] = 0;
    } else if (dir == 2) {
        board[y][x - 1].wall_dir[0] = 0;
    } else {
        board[y - 1][x].wall_dir[1] = 0;
    }

}
//assume (x, y) is a valid pixel
bool SquareMaze::outofBounce(int x, int y, int dir) {
    if (dir == 0) { //right
        if (x == (width_ - 1)) return true; //out of bounce
    } else if (dir == 1) { //down
        if (y == (height_ - 1)) return true; //out of bounce
    } else if (dir == 2) { //left
        if (x == 0) return true; //out of bounce
    } else { //up
        if (y == 0) return true; //out of bounce
    }
    return false;
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
            //wallsAtTiles_.push_back(std::vector<int> {1, 1, 1, 1});
        }
        board.push_back(vec);
        vec.clear();
    }
    width_ = width;
    height_ = height;

    d.addelements(width_ * height_);
    std::cout << "Here" << std::endl;
    while (d.size(0) != (width_ * height_)) {
        
        int x = rand() % width_;
        int y = rand() % height_;
        int randtile = y * width_ + x;
        std::cout << x << std::endl;
        std::cout << y << std::endl;
        std::cout << "Before" << std::endl;
        Tile t = board[y][x];
        std::cout << "After" << std::endl;
        int dir = rand() % 4;
        if (!outofBounce(x, y, dir) && t.wall_dir[dir] == 1) { //wall exists
            int neighbortile;
            if (dir == 0) {
                neighbortile = randtile + 1;
            } else if (dir == 1) {
                neighbortile = randtile + width_;
            } else if (dir == 2) {
                neighbortile = randtile - 1;
            } else {
                neighbortile = randtile - width_;
            }
            if (d.find(randtile) != d.find(neighbortile)) {
                deleteTile(x, y, dir); //only delete a tile if it does not create a cycle in graph
                d.setunion(randtile, neighbortile);
            }
            
        }
        

    }

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
        if (canTravel(x, y, dir)) {
            if (dir == 0) {
                board[y][x + 1].wall_dir[2] = 1;
            } else if (dir == 1) {
                board[y + 1][x].wall_dir[3] = 1;
            } else if (dir == 2) {
                board[y][x - 1].wall_dir[0] = 1;
            } else {
                board[y - 1][x].wall_dir[1] = 1;
            }
        }
    } else {
        t.wall_dir[dir] = 0;
        if (canTravel(x, y, dir)) {
            if (dir == 0) {
                board[y][x + 1].wall_dir[2] = 0;
            } else if (dir == 1) {
                board[y + 1][x].wall_dir[3] = 0;
            } else if (dir == 2) {
                board[y][x - 1].wall_dir[0] = 0;
            } else {
                board[y - 1][x].wall_dir[1] = 0;
            }
        }
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