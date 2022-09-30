#include <catch2/catch_test_macros.hpp>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.
  
  /*
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");
  */

  PNG png(40, 40);
  Point startPoint(20, 20);
  std::cout << "Hi" << std::endl;
  BFS bfs(png, startPoint, 0.2); //stuck for a while
  std::cout << "Hi" << std::endl;
  bfs.add( Point(2, 2) );
  bfs.add( Point(2, 3) );
  bfs.add( Point(2, 4) );

  //REQUIRE( bfs.peek() == Point(20, 20) );

  std::cout << bfs.peek() << std::endl;

  return 0;
}

