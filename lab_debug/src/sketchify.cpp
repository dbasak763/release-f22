/**
 * @file sketchify.cpp
 * Implementation of the sketchify function.
 */
#pragma GCC diagnostic ignored "-Wuninitialized"
#include <cstdlib>
#include <cmath>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
using namespace cs225;

/**
 * Creates a new output image.

 * @param w width of the image
 * @param h height of the image

 * @return a pointer to the newly-created image
 */
PNG* setupOutput(unsigned w, unsigned h) {
    PNG* image = new PNG(w, h);
    return image;
}

/**
 * Used to customize the color of the sketchified image.

 * @return a pointer to the color to use when sketchifying
 */
HSLAPixel* myFavoriteColor() {
    HSLAPixel* p = new HSLAPixel(13, 0.8, 0.5);
    return p;
}

void sketchify(std::string inputFile, std::string outputFile) {
    // Load in.png
    PNG* original = new PNG();
    //std::cout << "HI" << std::endl;
    original->readFromFile(inputFile);
    //std::cout << "HI" << std::endl;
    unsigned width = original->width();
    unsigned height = original->height();
    //std::cout << "HI" << std::endl;
    //Works up to this point
    // Create out.png
    PNG* output = new PNG();
    //std::cout << "HI" << std::endl;
    output = setupOutput(width, height);
    //std::cout << "HI" << std::endl;

    // Load our favorite color to color the outline
    HSLAPixel* myPixel = myFavoriteColor();

    //std::cout << "HI" << std::endl;

    // Go over the whole image, and if a pixel differs from that to its upper
    // left, color it my favorite color in the output
    for (unsigned y = 1; y < height; y++) {
        //std::cout << "height: " << height << std::endl;
        for (unsigned x = 1; x < width; x++) {
            //std::cout << "width: " << width << std::endl;
            // Calculate the pixel difference
            //std::cout << "HI" << std::endl;
            HSLAPixel& prev = original->getPixel(x - 1, y - 1);
            //std::cout << "HI" << std::endl;
            HSLAPixel& curr = original->getPixel(x, y);
            //std::cout << "HI" << std::endl;
            double diff = std::fabs(curr.h - prev.h);
            //std::cout << "HI" << std::endl;
            // If the pixel is an edge pixel,
            // color the output pixel with my favorite color
            HSLAPixel& currOutPixel = (*output).getPixel(x, y);
            //std::cout << "HI" << std::endl;
            if (diff > 20) {
                currOutPixel = *myPixel;
            }
            //std::cout << "HI" << std::endl;
        }
    }

    // Save the output file
    output->writeToFile(outputFile);

    // Clean up memory`
    //delete myPixel;
    delete output;
    delete original;
}
