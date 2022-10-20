/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include <utility>
#include <algorithm>

#include "maptiles.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
     MosaicCanvas* mosaiccanvas = new MosaicCanvas(theSource.getRows(), theSource.getColumns());

     std::map<Point<3>, TileImage*> m;
     vector<Point<3>> newPoints; //stores average values

     for (unsigned i = 0; i < theTiles.size(); i++) {
        TileImage* tileImg = &theTiles[i];
        Point<3> pt = convertToXYZ(tileImg->getAverageColor());
        m[pt] = tileImg;
        newPoints.push_back(pt);
     }

     KDTree kdtree(newPoints);

    for (int row = 0; row < mosaiccanvas->getRows(); row++) {
        for (int col = 0; col < mosaiccanvas->getColumns(); col++) {
            LUVAPixel luv1 = theSource.getRegionColor(row, col);
            Point<3> p1 = convertToXYZ(luv1);
            //do stuff here
            Point<3> nearestNeighbor = kdtree.findNearestNeighbor(p1);
            //more stuff
            mosaiccanvas->setTile(row, col, m[nearestNeighbor]);
        }
    }

    return mosaiccanvas;
}

