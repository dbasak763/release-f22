
#include <StickerSheet.h>

cs225::StickerSheet::StickerSheet(const Image& picture, unsigned max) {
//Initializes this StickerSheet with a deep copy of the base picture 
    basePicture = new Image(picture);
    stickers_ = new Image* [max];
    mx = max;
//and the ability to hold a max number of stickers (Images) with indices 0 through max - 1.
}
cs225::StickerSheet::~StickerSheet() {
//Frees all space that was dynamically allocated by this StickerSheet.
    delete[] stickers_;
    delete basePicture;
    points.clear();
}
cs225::StickerSheet::StickerSheet(const StickerSheet &other) {
//The copy constructor makes this StickerSheet an independent copy of the source.
    delete[] stickers_;
    delete basePicture;
    points.clear();
    basePicture = new Image(other.basePicture);
    stickers_ = new Image*[other.mx];
    for (unsigned index = 0; index < other.mx; index++) {
        stickers_[index] = other.stickers_[index];
        points.push_back(make_pair(other.stickers_.points.first, other.stickers_.points.second));
    }
    mx = other.mx;
}

const cs225::StickerSheet& cs225::StickerSheet::operator=(const StickerSheet &other) {
//The assignment operator for the StickerSheet class.
    delete[] stickers_;
    delete basePicture;
    basePicture = other.basePicture;
    stickers_ = new Image*[other.mx];
    for (unsigned index = 0; index < other.mx; index++) {
        stickers_[index] = other.stickers_[index];
    }
    mx = other.mx;
    return *this;
}

void cs225::StickerSheet::changeMaxStickers(unsigned max) {
//Modifies the maximum number of stickers that can be stored on this StickerSheet without changing existing stickers' indices.
    Image** newstickers_ = new Image*[max];
    for (unsigned i = 0; i < mx; i++) {
        newstickers_[i] = stickers_[i];
    }
    delete[] stickers_;
    stickers_ = newstickers_;
    mx = max;
//If the new maximum number of stickers is smaller than the current number number of stickers, the stickers with indices above max - 1 will be lost.
}

int cs225::StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y) {
//Adds a sticker to the StickerSheet, so that the top-left of the sticker's Image is at (x, y) on the StickerSheet.
    bool occupied = false;
    points.push_back(make_pair(x, y));
    for (unsigned i = 0; !occupied && (i < mx); i++) {
        if (stickers_[i] == NULL) {
            stickers_[i] = sticker;
            return i;
            occupied = true;
        }
    }
    if (!occupied) return -1;
//The sticker must be added to the lowest possible layer available.
}

bool cs225::StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
//Changes the x and y coordinates of the Image in the specified layer.
    if (index < 0 || index >= mx) return false;
    if (stickers_[index] == NULL) return false;
    points[index].first = x;
    points[index].second = y;
    return true;
//If the layer is invalid or does not contain a sticker, this function must return false. 

//Otherwise, this function returns true.
}

void cs225::StickerSheet::removeSticker(unsigned index) {
//Removes the sticker at the given zero-based layer index.
    
    if (index < 0 || index >= mx) return;
    stickers_[index] = NULL;
    points.pop_back();
//Make sure that the other stickers don't change order.
}

cs225::Image* cs225::StickerSheet::getSticker(unsigned index) {
//Returns a pointer to the sticker at the specified index, not a copy of it.
    if (index < 0 || index >= mx) return NULL;
    return stickers_[index];
//That way, the user can modify the Image.

//If the index is invalid, return NULL.
}

cs225::Image cs225::StickerSheet::render() const {
//Renders the whole StickerSheet on one Image and returns that Image.
    Image* newImage = new Image(basePicture);
//The base picture is drawn first and then each sticker is drawn in order starting with layer zero (0), then layer one (1), and so on.
    for (unsigned i = 0; i < mx; i++) {
        if (stickers_[i] == NULL) {
            continue;
        }
        //else draw the sticker to the newImage
        
    }
//If a pixel's alpha channel in a sticker is zero (0), no pixel is drawn for that sticker at that pixel. If the alpha channel is non-zero, a pixel is drawn. (Alpha blending is awesome, but not required.)
    return *newImage;
//The returned Image always includes the full contents of the picture and all stickers. This means that the size of the result image may be larger than the base picture if some stickers go beyond the edge of the picture.
}

