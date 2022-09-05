
#include <StickerSheet.h>

cs225::StickerSheet::StickerSheet(const Image& picture, unsigned max) {
//Initializes this StickerSheet with a deep copy of the base picture 
    basePicture = new Image(picture);
    stickers_ = new Image* [max];
    for (unsigned i = 0; i < max; i++) stickers_[i] = NULL;
    mx = max;
    points.clear();
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
    points.clear();
    delete basePicture;
    basePicture = NULL;
    basePicture = new Image(*other.basePicture);
    stickers_ = new Image*[other.mx];
    for (unsigned i = 0; i < other.mx; i++) stickers_[i] = NULL;
    unsigned layer = 0;
    for (unsigned index = 0; index < other.mx; index++) {
        stickers_[index] = other.stickers_[index];
        if (stickers_[index] != NULL) {
            points.push_back(std::make_pair(other.points[layer].first, other.points[layer].second));
            layer++;
        }
    }
    mx = other.mx;
}

const cs225::StickerSheet& cs225::StickerSheet::operator=(const StickerSheet &other) {
//The assignment operator for the StickerSheet class.
    delete[] stickers_;
    points.clear();
    delete basePicture;
    basePicture = NULL;
    basePicture = new Image(*other.basePicture);
    stickers_ = new Image*[other.mx];
    for (unsigned i = 0; i < other.mx; i++) stickers_[i] = NULL;
    unsigned layer = 0;
    for (unsigned index = 0; index < other.mx; index++) {
        stickers_[index] = other.stickers_[index];
        if (stickers_[index] != NULL) {
            points.push_back(std::make_pair(other.points[layer].first, other.points[layer].second));
            layer++;
        }
    }
    mx = other.mx;
    return *this;
}

void cs225::StickerSheet::changeMaxStickers(unsigned max) {
//Modifies the maximum number of stickers that can be stored on this StickerSheet without changing existing stickers' indices.
    if (max > mx) {
        Image** newstickers_ = new Image*[max];
        for (unsigned i = 0; i < mx; i++) {
            newstickers_[i] = stickers_[i];
        }
        for (unsigned i = mx; i < max; i++) {
            newstickers_[i] = NULL;
        }
        delete[] stickers_;
        stickers_ = newstickers_;
        mx = max;
    } else if (max < mx) { //logic is seg-faulting
        Image** newstickers_ = new Image*[max];
        for (unsigned i = 0; i < max; i++) {
            newstickers_[i] = stickers_[i];
        }
        unsigned int discardedLayers = 0;
        for (unsigned i = max; i < mx; i++) {
            if (stickers_[i] != NULL) {
                discardedLayers++;
            }
        }
        for (unsigned topLayer = 1; topLayer <= discardedLayers; topLayer++) points.pop_back();
        delete[] stickers_;
        stickers_ = newstickers_;
        mx = max;
    }
    
//If the new maximum number of stickers is smaller than the current number number of stickers, the stickers with indices above max - 1 will be lost.
}

int cs225::StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y) {
//Adds a sticker to the StickerSheet, so that the top-left of the sticker's Image is at (x, y) on the StickerSheet.
    points.push_back(std::make_pair(x, y));
    for (unsigned i = 0; i < mx; i++) {
        if (stickers_[i] == NULL) {
            stickers_[i] = &sticker;
            std::cout << stickers_[i]->width() << " " << stickers_[i]->height() << std::endl;
            return i;
        }
    }
    return -1;
//The sticker must be added to the lowest possible layer available.
}

bool cs225::StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
//Changes the x and y coordinates of the Image in the specified layer.
    if (index < 0 || index >= mx) return false;
    if (stickers_[index] == NULL) return false;
    unsigned layer = 0;
    for (unsigned i = 0; i < index; i++) {
        if (stickers_[i] != NULL) {
            layer++;
        }
    }
    points[layer].first = x;
    points[layer].second = y;
    return true;
//If the layer is invalid or does not contain a sticker, this function must return false. 

//Otherwise, this function returns true.
}

void cs225::StickerSheet::removeSticker(unsigned index) {
//Removes the sticker at the given zero-based layer index.
    
    if (index < 0 || index >= mx) return;
    stickers_[index] = NULL;
    unsigned bottomLayers = 0;
    for (unsigned i = 0; i < index; i++) {
        if (stickers_[i] != NULL) {
            bottomLayers++;
        }
    }
    points.erase(points.begin() + bottomLayers);
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
    unsigned maxWidth = 0;
    unsigned maxHeight = 0;
    unsigned layer = 0;
    //std::cout << "Hi" << std::endl;
    for (unsigned i = 0; i < mx; i++) {
        if (stickers_[i] != NULL)  {
            Image* image_ = stickers_[i];
            //std::cout << image_->width() << std::endl;
            maxWidth = std::max(maxWidth, image_->width() + points[layer].first);
            maxHeight = std::max(maxHeight, image_->height() + points[layer].second);
            layer++;
        }
       
    }
    maxWidth = std::max(maxWidth, basePicture->width());
    maxHeight = std::max(maxHeight, basePicture->height());
    //std::cout << "Hi" << std::endl;

    Image newImage;
    newImage.resize(maxWidth, maxHeight);
    //std::cout << maxWidth << " " << maxHeight << std::endl;
    
    for (unsigned x = 0; x < basePicture->width(); x++) {
        for (unsigned y = 0; y < basePicture->height(); y++) {
            HSLAPixel & oldPixel = basePicture->getPixel(x, y);
            HSLAPixel & newPixel = newImage.getPixel(x, y);
            if (oldPixel.a != 0.0) newPixel = oldPixel;
        }
    }
    
    //std::cout << "Hifdasfdsafdsasdf" << std::endl;

//The base picture is drawn first and then each sticker is drawn in order starting with layer zero (0), then layer one (1), and so on.
    layer = 0;
    for (unsigned i = 0; i < mx; i++) {
        if (stickers_[i] != NULL) {
            
        
        //else draw the sticker to the newImage
            Image* image_ = stickers_[i];
            for (unsigned x = 0; x < image_->width(); x++) {
                for (unsigned y = 0; y < image_->height(); y++) {
                    HSLAPixel & oldPixel = image_->getPixel(x, y);
                    HSLAPixel & newPixel = newImage.getPixel(points[layer].first + x, points[layer].second + y);
                    if (oldPixel.a != 0.0) newPixel = oldPixel;
                }
            }
            layer++;
        }
    }
//If a pixel's alpha channel in a sticker is zero (0), no pixel is drawn for that sticker at that pixel. If the alpha channel is non-zero, a pixel is drawn. (Alpha blending is awesome, but not required.)
    //std::cout << "Hifdasfdsafdsasdf" << std::endl;

    return newImage;
//The returned Image always includes the full contents of the picture and all stickers. This means that the size of the result image may be larger than the base picture if some stickers go beyond the edge of the picture.
}

