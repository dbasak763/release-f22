#include "cs225/PNG.h"
#include <list>
#include <iostream>

#include "colorPicker/ColorPicker.h"
#include "imageTraversal/ImageTraversal.h"

#include "Point.h"
#include "Animation.h"
#include "FloodFilledImage.h"

using namespace cs225;

/**
 * Constructs a new instance of a FloodFilledImage with a image `png`.
 * 
 * @param png The starting image of a FloodFilledImage
 */
FloodFilledImage::FloodFilledImage(const PNG & png) {
  png_ = png;
}

/**
 * Adds a FloodFill operation to the FloodFillImage.  This function must store the operation,
 * which will be used by `animate`.
 * 
 * @param traversal ImageTraversal used for this FloodFill operation.
 * @param colorPicker ColorPicker used for this FloodFill operation.
 */
void FloodFilledImage::addFloodFill(ImageTraversal & traversal, ColorPicker & colorPicker) {
  operations_.push_back(std::make_pair(&traversal, &colorPicker));
}

/**
 * Creates an Animation of frames from the FloodFill operations added to this object.
 * 
 * Each FloodFill operation added by `addFloodFill` is executed based on the order
 * the operation was added.  This is done by:
 * 1. Visiting pixels within the image based on the order provided by the ImageTraversal iterator and
 * 2. Updating each pixel to a new color based on the ColorPicker
 * 
 * While applying the FloodFill to the image, an Animation is created by saving the image
 * after every `frameInterval` pixels are filled.  To ensure a smooth Animation, the first
 * frame is always the starting image and the final frame is always the finished image.
 * 
 * (For example, if `frameInterval` is `4` the frames are:
 *   - The initial frame
 *   - Then after the 4th pixel has been filled
 *   - Then after the 8th pixel has been filled
 *   - ...
 *   - The final frame, after all pixels have been filed)
 */ 
Animation FloodFilledImage::animate(unsigned frameInterval) const {
  Animation animation;
  int pixelCount = 0;
  PNG pngcopy_ = PNG(png_);
  for (auto it = operations_.begin(); it != operations_.end(); it++) {
    ImageTraversal& traversal = *it->first;
    ColorPicker& colorPicker = *it->second;
    for (const Point & p : traversal) { 
        if (pixelCount % frameInterval == 0) {
          animation.addFrame(pngcopy_);
        }
        pixelCount++;
        //std::cout << "PNG getPixel value: " << pngcopy_.getPixel(p.x, p.y) << std::endl;
        //std::cout << "colorPicker getColor value at pixel: " << colorPicker.getColor(p.x, p.y) << std::endl;
        HSLAPixel hsla1 = colorPicker.getColor(p.x, p.y);
        HSLAPixel& hsla2 = pngcopy_.getPixel(p.x, p.y);
        hsla2 = hsla1;
        //std::cout << "HSLA1: " << hsla1 << " : " << "HSLA2: " << hsla2 << std::endl;
        //std::cout << pngcopy_.getPixel(p.x, p.y) << std::endl;
     }
  }
  //operations_.clear();
  animation.addFrame(pngcopy_);
  return animation;
}
