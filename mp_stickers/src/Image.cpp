#include <Image.h>

void cs225::Image::lighten() {
//Lighten an Image by increasing the luminance of every pixel by 0.1.

//This function ensures that the luminance remains in the range [0, 1].
}
void cs225::Image::lighten(double amount) {
//Lighten an Image by increasing the luminance of every pixel by amount.

//This function ensures that the luminance remains in the range [0, 1].
}
void cs225::Image::darken() {
//Darken an Image by decreasing the luminance of every pixel by 0.1.

//This function ensures that the luminance remains in the range [0, 1].
}
void cs225::Image::darken(double amount) {
//Darkens an Image by decreasing the luminance of every pixel by amount.

//This function ensures that the luminance remains in the range [0, 1].
}
void cs225::Image::saturate() {
//Saturates an Image by increasing the saturation of every pixel by 0.1.

//This function ensures that the saturation remains in the range [0, 1].
}
void cs225::Image::saturate(double amount) {
//Saturates an Image by increasing the saturation of every pixel by amount.

//This function ensures that the saturation remains in the range [0, 1].
}
void cs225::Image::desaturate() {
//Desaturates an Image by decreasing the saturation of every pixel by 0.1.

//This function ensures that the saturation remains in the range [0, 1].
}

void cs225::Image::desaturate(double amount) {
//Desaturates an Image by decreasing the saturation of every pixel by amount.

//This function ensures that the saturation remains in the range [0, 1].
}

void cs225::Image::grayscale() {
//Turns the image grayscale by setting saturation of all pixels to 0.
}

void cs225::Image::rotateColor(double degrees) {
//Rotates the color wheel by degrees.

//Rotating in a positive direction increases the degree of the hue. This function ensures that the hue remains in the range [0, 360].
}

void cs225::Image::illinify() {
//Transform an Image to Illini colors.

//The hue of every pixel is set to the a hue value of either orange or blue, based on if the pixel's hue value is closer to orange than blue.
}

void cs225::Image::scale(double factor) {
//Scale the Image by a given factor.
/*
For example:

A factor of 1.0 does not change the image.
A factor of 0.5 results in an image with half the width and half the height.
A factor of 2 results in an image with twice the width and twice the height.
*/
}

void cs225::Image::scale(unsigned w, unsigned h) {
//Scales the image to fit within the size (w x h).

//This function preserves the aspect ratio of the image, so the result will always be an image of width w or of height h (not necessarily both).

//For example, if the Image is currently (10, 20) and we want to scale to (100, 100), then this should scale the Image to (50, 100). Note that scaling the image to (100, 200) does not fit within the (100,100) dimensions given and is therefore incorrect.

//This function both resizes the Image and scales the contents.
}

