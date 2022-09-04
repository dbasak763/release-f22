
#include <StickerSheet.h>

cs225::StickerSheet::StickerSheet(const Image& picture, unsigned max) {
//Initializes this StickerSheet with a deep copy of the base picture 
    basePicture = new Image(picture);
    stickers_ = new Image* [max];
    sz = max;
//and the ability to hold a max number of stickers (Images) with indices 0 through max - 1.
}
cs225::StickerSheet::~StickerSheet() {
//Frees all space that was dynamically allocated by this StickerSheet.
    delete[] stickers_;
    delete basePicture;
    sz = 0;
}
cs225::StickerSheet::StickerSheet(const StickerSheet &other) {
//The copy constructor makes this StickerSheet an independent copy of the source.
    delete[] stickers_;
    delete basePicture;
    basePicture = other.basePicture;
    stickers_ = new Image*[other.sz];
    for (unsigned index = 0; index < other.sz; index++) {
        stickers_[index] = other.stickers_[index];
    }
    sz = other.sz;
}

const cs225::StickerSheet& cs225::StickerSheet::operator=(const StickerSheet &other) {
//The assignment operator for the StickerSheet class.
    delete[] stickers_;
    delete basePicture;
    basePicture = other.basePicture;
    stickers_ = new Image*[other.sz];
    for (unsigned index = 0; index < other.sz; index++) {
        stickers_[index] = other.stickers_[index];
    }
    sz = other.sz;
    return *this;
}

void cs225::StickerSheet::changeMaxStickers(unsigned max) {
//Modifies the maximum number of stickers that can be stored on this StickerSheet without changing existing stickers' indices.
    Image** newstickers_ = new Image*[max];
    std::copy(stickers_, stickers_ + std::min(sz, max), newstickers_);
    delete[] stickers_;
    stickers_ = newstickers_;
    sz = max;
//If the new maximum number of stickers is smaller than the current number number of stickers, the stickers with indices above max - 1 will be lost.
}

int cs225::StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y) {
//Adds a sticker to the StickerSheet, so that the top-left of the sticker's Image is at (x, y) on the StickerSheet.
    return 0;
//The sticker must be added to the lowest possible layer available.
}

bool cs225::StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
//Changes the x and y coordinates of the Image in the specified layer.
    return false;
//If the layer is invalid or does not contain a sticker, this function must return false. 

//Otherwise, this function returns true.
}

void cs225::StickerSheet::removeSticker(unsigned index) {
//Removes the sticker at the given zero-based layer index.

//Make sure that the other stickers don't change order.
}

cs225::Image* cs225::StickerSheet::getSticker(unsigned index) {
//Returns a pointer to the sticker at the specified index, not a copy of it.
    return stickers_[index];
//That way, the user can modify the Image.

//If the index is invalid, return NULL.
}

cs225::Image cs225::StickerSheet::render() const {
//Renders the whole StickerSheet on one Image and returns that Image.

//The base picture is drawn first and then each sticker is drawn in order starting with layer zero (0), then layer one (1), and so on.
    return *basePicture;
//If a pixel's alpha channel in a sticker is zero (0), no pixel is drawn for that sticker at that pixel. If the alpha channel is non-zero, a pixel is drawn. (Alpha blending is awesome, but not required.)

//The returned Image always includes the full contents of the picture and all stickers. This means that the size of the result image may be larger than the base picture if some stickers go beyond the edge of the picture.
}

