#include "Image.h"

#include <iostream>

int main() {
  cs225::Image alma;

  std::cout << "Using Image::lighten to create `lighten.png`..." << std::endl;
  alma.readFromFile("../alma.png");
  alma.lighten(0.2);
  alma.writeToFile("../lighten.png");

  std::cout << "Using Image::lighten to create `rotateColor.png`..." << std::endl;
  alma.readFromFile("../alma.png");
  alma.rotateColor(130.18);
  alma.writeToFile("../rotateColor.png");

  std::cout << "Using Image::saturate to create `saturate.png`..." << std::endl;
  alma.readFromFile("../alma.png");
  alma.saturate(0.2);
  alma.writeToFile("../saturate.png");

  std::cout << "Using Image::scale to create `scale.png`..." << std::endl;
  alma.readFromFile("../alma.png");
  alma.scale(2);
  alma.writeToFile("../scale2x.png");

  std::cout << "Using Image::Illinify to create `illinify.png`..." << std::endl;
  alma.readFromFile("../alma.png");
  alma.illinify();
  alma.writeToFile("../illinify.png");

  std::cout << "Using Image::scale to create `scale3x.png`..." << std::endl;
  alma.readFromFile("../alma.png");
  alma.scale(300, 150);
  alma.writeToFile("../scale3x.png");

  return 0;
}
