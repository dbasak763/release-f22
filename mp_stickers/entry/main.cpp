#include "Image.h"
#include "StickerSheet.h"
using namespace cs225;
int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image alma; alma.readFromFile("../tests/alma.png");
  Image i;    i.readFromFile("../tests/i.png");
  Image expected; expected.readFromFile("../tests/expected.png");
  Image expected2; expected2.readFromFile("../tests/expected-2.png");
  //std::cout << "Hi" << std::endl;
  StickerSheet s1(alma, 3);
  s1.addSticker(i, 20, 200);
  s1.addSticker(i, 40, 200);
  s1.addSticker(i, 60, 200);
  //std::cout << "Hi" << std::endl;

  Image rendered = s1.render();
  rendered.writeToFile("../myImage.png");
  
  
  
  return 0;
}
