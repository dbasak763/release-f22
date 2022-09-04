#include <Image.h>

void cs225::Image::lighten() {
//Lighten an Image by increasing the luminance of every pixel by 0.1.
    for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {
         HSLAPixel & pixelAtLocation = this->getPixel(x, y);
         pixelAtLocation.l += 0.1;
      }
    }
//This function ensures that the luminance remains in the range [0, 1].
}
void cs225::Image::lighten(double amount) {
//Lighten an Image by increasing the luminance of every pixel by amount.
    for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {
         HSLAPixel & pixelAtLocation = this->getPixel(x, y);
         pixelAtLocation.l += amount;
      }
    }
//This function ensures that the luminance remains in the range [0, 1].
}
void cs225::Image::darken() {
//Darken an Image by decreasing the luminance of every pixel by 0.1.
    for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {
         HSLAPixel & pixelAtLocation = this->getPixel(x, y);
         pixelAtLocation.l -= 0.1;
      }
    }
//This function ensures that the luminance remains in the range [0, 1].
}
void cs225::Image::darken(double amount) {
//Darkens an Image by decreasing the luminance of every pixel by amount.
    for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {
         HSLAPixel & pixelAtLocation = this->getPixel(x, y);
         pixelAtLocation.l -= amount;
      }
    }
//This function ensures that the luminance remains in the range [0, 1].
}
void cs225::Image::saturate() {
//Saturates an Image by increasing the saturation of every pixel by 0.1.
    for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {
         HSLAPixel & pixelAtLocation = this->getPixel(x, y);
         pixelAtLocation.s += 0.1;
      }
    }
//This function ensures that the saturation remains in the range [0, 1].
}
void cs225::Image::saturate(double amount) {
//Saturates an Image by increasing the saturation of every pixel by amount.
    for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {
         HSLAPixel & pixelAtLocation = this->getPixel(x, y);
         pixelAtLocation.s += amount;
      }
    }
//This function ensures that the saturation remains in the range [0, 1].
}
void cs225::Image::desaturate() {
//Desaturates an Image by decreasing the saturation of every pixel by 0.1.
    for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {
         HSLAPixel & pixelAtLocation = this->getPixel(x, y);
         pixelAtLocation.s -= 0.1;
      }
    }
//This function ensures that the saturation remains in the range [0, 1].
}

void cs225::Image::desaturate(double amount) {
//Desaturates an Image by decreasing the saturation of every pixel by amount.
    for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {
         HSLAPixel & pixelAtLocation = this->getPixel(x, y);
         pixelAtLocation.s -= amount;
      }
    }
//This function ensures that the saturation remains in the range [0, 1].
}

void cs225::Image::grayscale() {
//Turns the image grayscale by setting saturation of all pixels to 0.
    for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {
         HSLAPixel & pixelAtLocation = this->getPixel(x, y);
         pixelAtLocation.s = 0;
      }
    }
}

void cs225::Image::rotateColor(double degrees) {
//Rotates the color wheel by degrees.
    for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {
         HSLAPixel & pixelAtLocation = this->getPixel(x, y);
         double sum = pixelAtLocation.h + degrees;
         double decimal = sum - (int)(sum);
         pixelAtLocation.h = (int)(sum) % 360 + decimal;
      }
    }
//Rotating in a positive direction increases the degree of the hue. This function ensures that the hue remains in the range [0, 360].
}

void cs225::Image::illinify() {
//Transform an Image to Illini colors.
    for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {
         HSLAPixel & pixelAtLocation = this->getPixel(x, y);
         if (pixelAtLocation.h < 113.5) {
            pixelAtLocation.h = 11;
         } else {
            pixelAtLocation.h = 216;
         }
      }
    }
//The hue of every pixel is set to the a hue value of either orange or blue, based on if the pixel's hue value is closer to orange than blue.
}

void cs225::Image::scale(double factor) {
    resize(width() * factor, height() * factor);
}

void cs225::Image::scale(unsigned w, unsigned h) {
    //Calculate ratios of new width to original width, and new height to original height
    unsigned r_width = w / width();
    unsigned r_height = h / height();

    if (r_width < r_height) { //scale so that new width is matched, new height maintains scale ratio
        resize(w, height() * r_width);
    } else {
        resize(width() * r_height, h);
    }
}

