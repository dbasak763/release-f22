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
    if (!board.empty()) {
        for (unsigned i = 0; i < board.size(); i++) {
            board[i].clear();
        }
        board.clear();
    }

    width_ = width;
    height_ = height;



    for (int i = 0; i < height; i++) { //row is y_index
        std::vector<Tile> vec;
        std::vector<bool> visitedRow;
        for (int j = 0; j < width; j++) { //col is x_index
            Tile t = Tile();
            t.x_index = i;
            t.y_index = j;
            vec.push_back(t);
            visitedRow.push_back(false);
        }
        board.push_back(vec);
        visited.push_back(visitedRow);
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
        if (x == (width_ - 1)) return false;
        return (t.wall_dir[0] == 0); //no wall present, so can traverse
    } else if (dir == 1) { //down
        if (y == (height_ - 1)) return false;
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
    int longestPath = 0;
    std::vector<int> finalDirections;
    for (int col = 0; col < width_; col++) {
        //visited.resize(width_ * height_, false);
        for (int i = 0; i < height_; i++) {
            for (int j = 0; j < width_; j++) {
                visited[i][j] = false;
            }
        }
        int distOfPath = 0;
        //std::vector<int> directions;
        Tile startingTile = board[height_ - 1][col];
        //perform a bfs
        queue.push(std::make_pair(std::make_pair(startingTile, 0), ""));

        std::string fullReversePath = "";
        
        while (!queue.empty()) {
            Tile currTile = queue.front().first.first;
            int distFromStartingTile = queue.front().first.second;
            std::string currPath = queue.front().second;

            //std::cout << "Visited tile: ( " << currTile.x_index << ", " << currTile.y_index << " )" << std::endl;
            //std::cout << "Dist From Starting Tile: " << distFromStartingTile << std::endl;
            //std::cout << "Current Path : " << currPath << std::endl;

            visited[currTile.x_index][currTile.y_index] = true;
            
            if (currTile.x_index == 0 && currTile.y_index == 0) { //if we reached origin
                distOfPath = distFromStartingTile;
                fullReversePath = currPath;
                break;
            }
            queue.pop();

            while (!queue.empty() && visited[queue.front().first.first.x_index][queue.front().first.first.y_index]) {
                queue.pop();
            }

            if (canTravel(currTile.y_index, currTile.x_index, 0) && !visited[currTile.x_index][currTile.y_index + 1]) { //if rightneighbor can be visited
                Tile rightTile = board[currTile.x_index][currTile.y_index + 1];
                queue.push(std::make_pair(std::make_pair(rightTile, distFromStartingTile + 1), currPath + "0"));
            }
            if (canTravel(currTile.y_index, currTile.x_index, 1) && !visited[currTile.x_index + 1][currTile.y_index]) { //if downneighbor can be visited
                Tile downTile = board[currTile.x_index + 1][currTile.y_index];
                queue.push(std::make_pair(std::make_pair(downTile, distFromStartingTile + 1), currPath + "1"));
            }
            if (canTravel(currTile.y_index, currTile.x_index, 2) && !visited[currTile.x_index][currTile.y_index - 1]) { //if leftneighbor can be visited
                Tile leftTile = board[currTile.x_index][currTile.y_index - 1];
                queue.push(std::make_pair(std::make_pair(leftTile, distFromStartingTile + 1), currPath + "2"));
            }
            if (canTravel(currTile.y_index, currTile.x_index, 3) && !visited[currTile.x_index - 1][currTile.y_index]) { //if upneighbor can be visited
                Tile upTile = board[currTile.x_index - 1][currTile.y_index];
                queue.push(std::make_pair(std::make_pair(upTile, distFromStartingTile + 1), currPath + "3"));
            }
        }
        while (!queue.empty()) queue.pop();
        if (distOfPath > longestPath) {
            finalDirections.clear();
            longestPath = distOfPath;
            for (int i = fullReversePath.length() - 1; i >= 0; i--) {
                char c = fullReversePath[i];
                int dir;
                if (c == '0') {
                    dir = 2;
                } else if (c == '1') {
                    dir = 3;
                } else if (c == '2') {
                    dir = 0;
                } else {
                    dir = 1;
                }
                finalDirections.push_back(dir);
            }
        }
    }
    return finalDirections;
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