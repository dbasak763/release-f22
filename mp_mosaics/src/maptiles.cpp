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

     std::map<Point<3>, TileImage> m;
     vector<Point<3>> newPoints; //stores average values

     for (int i = 0; i < theTiles.size(); i++) {
        TileImage tileImg = theTiles[i];
        Point<3> pt = convertToXYZ(tileImg.getAverageColor());
        m[pt] = tileImg;
        newPoints.push_back(pt);
     }

     

     

     KDTree kdtree(const vector<Point<Dim>>& newPoints);

    findNearestNeighbor(const Point<3>& query, int dim, KDTreeNode * currRoot)

    for (unsigned row = 0; row < mosaiccanvas->getRows(); row++) {
        for (unsigned col = 0; col < mosaiccanvas->getColumns(); col++) {
            LUVAPixel luv1 = theSource->getRegionColor(row, col);
            Point<3> p1 = convertToXYZ(luv1);
            unsigned closest_tile_index = -1;
            double min_diff_colors_squared = 999;
            for (unsigned tile = 0; tile < theTiles.size(); tile++) {
                TileImage tileImage = theTiles[tile];
                LUVAPixel luv2 = tileImage.getAverageColor();
                Point<3> p2 = convertToXYZ(luv2);
                double diff_colors_squared = (p1[0] - p2[0]) * (p1[0] - p2[0]) + (p1[1] - p2[1]) * (p1[1] - p2[1]) + (p1[2] - p2[2]) * (p1[2] - p2[2]);
                if (diff_colors_squared < min_diff_colors_squared) {
                    min_diff_colors_squared = diff_colors_squared;
                    closest_tile_index = tile;
                }
            }
            TileImage* closestTile = &theTiles[closest_tile_index];
            mosaiccanvas->setTile(row, col, closestTile);
        }
    }

    return mosaiccanvas;
}

