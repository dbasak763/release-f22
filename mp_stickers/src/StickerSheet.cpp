
#include <StickerSheet.h>

StickerSheet::StickerSheet(const Image& picture, unsigned max) {
//Initializes this StickerSheet with a deep copy of the base picture 
//and the ability to hold a max number of stickers (Images) with indices 0 through max - 1.
}
StickerSheet::~StickerSheet() {
//Frees all space that was dynamically allocated by this StickerSheet.
}
StickerSheet::StickerSheet(const StickerSheet &other) {
//The copy constructor makes this StickerSheet an independent copy of the source.
}

const StickerSheet& StickerSheet::operator=(const StickerSheet &other) {
//The assignment operator for the StickerSheet class.
}

void StickerSheet::changeMaxStickers(unsigned max) {
//Modifies the maximum number of stickers that can be stored on this StickerSheet without changing existing stickers' indices.
//If the new maximum number of stickers is smaller than the current number number of stickers, the stickers with indices above max - 1 will be lost.
}

int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y) {
//Adds a sticker to the StickerSheet, so that the top-left of the sticker's Image is at (x, y) on the StickerSheet.

//The sticker must be added to the lowest possible layer available.
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
//Changes the x and y coordinates of the Image in the specified layer.

//If the layer is invalid or does not contain a sticker, this function must return false. 

//Otherwise, this function returns true.
}

void StickerSheet::removeSticker(unsigned index) {
//Removes the sticker at the given zero-based layer index.

//Make sure that the other stickers don't change order.
}

Image* StickerSheet::getSticker(unsigned index) {
//Returns a pointer to the sticker at the specified index, not a copy of it.

//That way, the user can modify the Image.

//If the index is invalid, return NULL.
}

Image StickerSheet::render() const {
//Renders the whole StickerSheet on one Image and returns that Image.

//The base picture is drawn first and then each sticker is drawn in order starting with layer zero (0), then layer one (1), and so on.

//If a pixel's alpha channel in a sticker is zero (0), no pixel is drawn for that sticker at that pixel. If the alpha channel is non-zero, a pixel is drawn. (Alpha blending is awesome, but not required.)

//The returned Image always includes the full contents of the picture and all stickers. This means that the size of the result image may be larger than the base picture if some stickers go beyond the edge of the picture.
}

