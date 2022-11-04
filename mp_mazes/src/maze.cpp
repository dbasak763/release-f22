/* Your code here! */
#include "maze.h"

SquareMaze::SquareMaze() {
    //can leave this empty
}
//assume that tile in direction can be traveled
void SquareMaze::deleteWall(int x, int y, int dir) {
    board[x][y].wall_dir[dir] = 0;
}
//assume (x, y) is a valid pixel
bool SquareMaze::outofBounce(int x, int y, int dir) {
    if (dir == 0) { //right
        if (y == (width_ - 1)) return true; //out of bounce
    } else if (dir == 1) { //down
        if (x == (height_ - 1)) return true; //out of bounce
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

    width_ = width;
    height_ = height;

    for (int i = 0; i < height; i++) { //row is y_index
        std::vector<Tile> vec;
        for (int j = 0; j < width; j++) { //col is x_index
            Tile t = Tile();
            t.x_index = i;
            t.y_index = j;
            vec.push_back(t);
        }
        board.push_back(vec);
    }

    d.addelements(width_ * height_);
    while (d.size(0) != (width_ * height_)) {
        
        int y = rand() % width_;
        int x = rand() % height_;
        int randtile = x * width_ + y;

        Tile t = board[x][y];
        int dir = rand() % 2;

        if (!outofBounce(x, y, dir) && t.wall_dir[dir] == 1) { //wall exists
            int neighbortile = 0;
            if (dir == 0) {
                neighbortile = randtile + 1;
            } else if (dir == 1) {
                neighbortile = randtile + width_;
            } 
            if (d.find(randtile) != d.find(neighbortile)) {
                deleteWall(x, y, dir); //only delete a tile if it does not create a cycle in graph
                d.setunion(randtile, neighbortile);
            }
            
        }
        
    }
    //d.print();
    /*
    for (int i = 0; i < height_; i++) {
        for (int j = 0; j < width_; j++) {
            //std::cout << "(" << board[i][j].wall_dir[0] << "," << board[i][j].wall_dir[1] << ") ";
        }
        //std::cout << std::endl;
    }
    */
    //need to add randomly deleting walls part such that no cycle appears in our graph(we have a tree), until no more edges can be deleted

}
//assume (x, y) is a valid tile location
bool SquareMaze::canTravel(int x, int y, int dir) const {
    Tile t = board[y][x];
    if (dir == 0) { //right
        return (t.wall_dir[0] == 0); //no wall present, so can traverse
    } else if (dir == 1) { //down
        return (t.wall_dir[1] == 0); //no wall present, so can traverse
    } else if (dir == 2) {
        if (x == 0) return false;
        return board[y][x-1].wall_dir[0] == 0;
    } else {
        if (y == 0) return false;
        return board[y-1][x].wall_dir[1] == 0;
    }
}

void SquareMaze::setWall(int x, int y, int dir, bool exists) {
    Tile &t = board[y][x];
    if (exists) {
        t.wall_dir[dir] = 1;
    }
    else {
        t.wall_dir[dir] = 0;
    }
}

std::vector<int> SquareMaze::solveMaze() {
    return std::vector<int>();
}


PNG* SquareMaze::drawMaze() const {
    
    PNG* png = new PNG(width_ * 10 + 1, height_ * 10 + 1);
    for (int col = 0; col < width_ * 10 + 1; col++) { //topmost row
        HSLAPixel &pixel = png->getPixel(0, col);
        pixel = HSLAPixel(0, 0, 0, 1);
    }
    for (int row = 10; row < height_ * 10 + 1; row++) { //leftmost col
        HSLAPixel &pixel = png->getPixel(row, 0);
        pixel = HSLAPixel(0, 0, 0, 1);
    }
    for (int i = 0; i < height_; i++) {
        for (int j = 0; j < width_; j++) {
            Tile t = board[i][j];
            int x_coord = t.x_index;
            int y_coord = t.y_index;
            
            if (t.wall_dir[0] == 1) { //right wall exists
                for (int k = 0; k <= 10; k++) {
                    HSLAPixel &pixel = png->getPixel((y_coord + 1) * 10, x_coord * 10 + k);
                    pixel = HSLAPixel(0, 0, 0, 1);
                }
            }
            if (t.wall_dir[1] == 1) { //bottom wall exists
                for (int k = 0; k <= 10; k++) {
                    HSLAPixel &pixel = png->getPixel(y_coord * 10 + k, (x_coord + 1) * 10);
                    pixel = HSLAPixel(0, 0, 0, 1);
                }
            }
        }
    }
    
    return png;

    
}

PNG* SquareMaze::drawMazeWithSolution() {
    PNG* maze_ = drawMaze();
    std::vector<int> solP = solveMaze();
    return maze_;
}