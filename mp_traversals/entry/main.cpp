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
  PNG png;       
  png.readFromFile("../tests/pacman.png");
  FloodFilledImage image(png);
  
  HSLAPixel h1 = HSLAPixel(0.14, 0.21, 0.27, 0.31);
  HSLAPixel h2 = HSLAPixel(0.18, 0.43, 0.77, 0.64);
  Point p1 = Point(40, 40);

  HSLAPixel h3 = HSLAPixel(0.76, 0.64, 0.32, 0.45);
  HSLAPixel h4 = HSLAPixel(0.23, 0.41, 1.32, 2.23);
  Point p2 = Point(120, 60);

  DFS dfs(png, Point(40, 40), 0.05);
  MyColorPicker mycolor1(h1, h2, p1, 31);
  image.addFloodFill( dfs, mycolor1 );
  BFS bfs(png, Point(60, 40), 0.67);
  MyColorPicker mycolor2(h3, h4, p2, 22);
  image.addFloodFill( bfs, mycolor2 );

  Animation animation = image.animate(536);

  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");
  
  


  return 0;
}

