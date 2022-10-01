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
  /*
  HSLAPixel blackPixel(180, 1, 0);
  
  for (unsigned i = 0; i < 4; i++) {
    png.getPixel(i, 0) = blackPixel;
    png.getPixel(0, i) = blackPixel;
    png.getPixel(i, 3) = blackPixel;
    png.getPixel(3, i) = blackPixel;
  }
  */
  PNG png(4, 4);
  HSLAPixel blackPixel(180, 1, 0);
  
  for (unsigned i = 0; i < 4; i++) {
    png.getPixel(i, 0) = blackPixel;
    png.getPixel(0, i) = blackPixel;
    png.getPixel(i, 3) = blackPixel;
    png.getPixel(3, i) = blackPixel;
  }

  Point startPoint(0, 0);
  
  DFS t(png, startPoint, 0.2);
  unsigned count = 0;
  std::cout << "Hi" << std::endl;
  for (const Point & p : t) { 
    count++; 
  }
  std::cout << count << std::endl; //should be 4
  return 0;
}

