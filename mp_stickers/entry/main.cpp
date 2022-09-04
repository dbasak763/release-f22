#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  cs225::Image alma, b, c, d;
  alma.readFromFile("../alma.png");
  b.readFromFile("../i.png");
  c.readFromFile("../i.png");
  d.readFromFile("../i.png");
  StickerSheet sheet = new StickerSheet(alma, 6);
  sheet.addSticker(b, 30, 60);
  sheet.addSticker(c, 240, 300);
  sheet.addSticker(d, 90, 175);
  return 0;
}
