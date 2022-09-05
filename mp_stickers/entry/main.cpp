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
  StickerSheet s1(alma, 5);
  s1.addSticker(i, 20, 200);
  s1.addSticker(i, 40, 200);
  //std::cout << "Hi" << std::endl;

  StickerSheet s2(s1); //error happens here when i am freeing something i should not be
  //std::cout << "Hi" << std::endl;
  /*
  s2.removeSticker(1);
  //std::cout << "Hi" << std::endl;
  Image rendered1 = s1.render();
  std::cout << "Hidfasfds" << std::endl;
  Image rendered2 = s2.render();
  std::cout << "Hidfasfds" << std::endl;
  rendered1.writeToFile("../rendered1.png"); //should match expected2
  rendered2.writeToFile("../rendered2.png"); //should match expected
  std::cout << "Hidfasds" << std::endl;
  
  */
  return 0;
}
