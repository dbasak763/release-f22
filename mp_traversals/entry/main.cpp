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
  PNG png;       png.readFromFile("../tests/i.png");
  PNG expected;  expected.readFromFile("../tests/i-rainbow-dfs.png");
  PNG expected2; expected2.readFromFile("../tests/i-rainbow-dfs-2.png");
  
  FloodFilledImage image(png);
  DFS dfs(png, Point(40, 40), 0.05);
  RainbowColorPicker rainbow(0.05);
  image.addFloodFill( dfs, rainbow );

  Animation animation = image.animate(1000);
  
  if( animation.frameCount() > 2 ) std::cout << "True" << std::endl;
  PNG secondFrame = animation.getFrame(1);
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );

  secondFrame.writeToFile("../i-rainbow-dfs-2.png");
  lastFrame.writeToFile("../i-rainbow-dfs.png");
  animation.write("../i-rainbow-dfs.gif");
  //INFO("Files written to i-rainbow-dfs-* for debugging.");
  
  if ( secondFrame == expected2 ) std::cout << "True Hi1" << std::endl;
  if ( lastFrame == expected ) std::cout << "True Hi2" << std::endl;

  return 0;
}

