#include <Image.h>

void cs225::Image::lighten() {
//Lighten an Image by increasing the luminance of every pixel by 0.1.
    for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {
         HSLAPixel & pixelAtLocation = this->getPixel(x, y);
         pixelAtLocation.l += 0.1;
         if (pixelAtLocation.l > 1.0) pixelAtLocation.l = 1.0;
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
         if (pixelAtLocation.l > 1.0) pixelAtLocation.l = 1.0;
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
         if (pixelAtLocation.l < 0.0) pixelAtLocation.l = 0.0;
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
         if (pixelAtLocation.l < 0.0) pixelAtLocation.l = 0.0;
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
         if (pixelAtLocation.s > 1.0) pixelAtLocation.s = 1.0;
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
         if (pixelAtLocation.s > 1.0) pixelAtLocation.s = 1.0;
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
         if (pixelAtLocation.s < 0.0) pixelAtLocation.s = 0.0;
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
         if (pixelAtLocation.s < 0.0) pixelAtLocation.s = 0.0;
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
    unsigned oldWidth = width();
    unsigned oldHeight = height();
    unsigned newWidth = width() * factor;
    unsigned newHeight = height() * factor;

    //HSLAPixel * oldImageData = _copy(imageData_);
    PNG * oldImage = new PNG(oldWidth, oldHeight);

    for (unsigned x = 0; x < oldWidth; x++) {
      for (unsigned y = 0; y < oldHeight; y++) {
         oldImage->getPixel(x, y) = getPixel(x, y);
      }
    }

    resize(newWidth,newHeight);

    //HSLAPixel * newImageData = new HSLAPixel[newWidth * newHeight];

    //PNG * newImage = new PNG(newWidth, newHeight);

    for (unsigned x = 0; x < newWidth; x++) {
      for (unsigned y = 0; y < newHeight; y++) {
         HSLAPixel & newPixel = this->getPixel(x, y);
         HSLAPixel & oldPixel = oldImage->getPixel(x * oldWidth / newWidth, y * oldHeight / newHeight);
         newPixel = oldPixel;
      }
    }

    delete oldImage;
    //this = newImage;

    //_copy(newImage);

    //have to scale contents as well, not just resize them
}

void cs225::Image::scale(unsigned w, unsigned h) {
    
    unsigned oldWidth = width();
    unsigned oldHeight = height();
    unsigned newWidth = w;
    unsigned newHeight = h;

    double factor = std::min(newWidth / (double)oldWidth, newHeight / (double)oldHeight);
    newWidth = oldWidth * factor;
    newHeight = oldHeight * factor;
    //HSLAPixel * oldImageData = _copy(imageData_);
    PNG * oldImage = new PNG(oldWidth, oldHeight);

    for (unsigned x = 0; x < oldWidth; x++) {
      for (unsigned y = 0; y < oldHeight; y++) {
         oldImage->getPixel(x, y) = getPixel(x, y);
      }
    }

    resize(newWidth, newHeight);

    //HSLAPixel * newImageData = new HSLAPixel[newWidth * newHeight];

    //PNG * newImage = new PNG(newWidth, newHeight);

    for (unsigned x = 0; x < newWidth; x++) {
      for (unsigned y = 0; y < newHeight; y++) {
         HSLAPixel & newPixel = this->getPixel(x, y);
         HSLAPixel & oldPixel = oldImage->getPixel(x * oldWidth / newWidth, y * oldHeight / newHeight);
         newPixel = oldPixel;
      }
    }

    delete oldImage;

}

