#include <cmath>
#include <iterator>
#include <iostream>

#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}
//Non-default iterator constructor
ImageTraversal::Iterator::Iterator(ImageTraversal* trav, Point startPoint) {
   traversal = trav;
   start = startPoint;
   current = traversal -> peek();
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  traversal = NULL;
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
    Point point = traversal->pop();
    visitedPoints.push_back(point);

    Point up = Point(point.x, point.y - 1);
    Point down = Point(point.x, point.y + 1);
    Point left = Point(point.x - 1, point.y);
    Point right = Point(point.x + 1, point.y);

    bool found_left = (std::find(visitedPoints.begin(), visitedPoints.end(), left) != visitedPoints.end());
    bool found_right = (std::find(visitedPoints.begin(), visitedPoints.end(), right) != visitedPoints.end());
    bool found_up = (std::find(visitedPoints.begin(), visitedPoints.end(), up) != visitedPoints.end());
    bool found_down = (std::find(visitedPoints.begin(), visitedPoints.end(), down) != visitedPoints.end());

    bool within_bounds_left = (left.x >= 0 && left.x < traversal->height_ && left.y >= 0 && left.y < traversal->width_);
    bool within_bounds_right = (right.x >= 0 && right.x < traversal->height_ && right.y >= 0 && right.y < traversal->width_);
    bool within_bounds_up = (up.x >= 0 && up.x < traversal->height_ && up.y >= 0 && up.y < traversal->width_);
    bool within_bounds_down = (down.x >= 0 && down.x < traversal->height_ && down.y >= 0 && down.y < traversal->width_); 

    if (within_bounds_right && !found_right) {
      HSLAPixel p1 = traversal->png_.getPixel(traversal->startPoint.x, traversal->startPoint.y);
      HSLAPixel p2 = traversal->png_.getPixel(right.x, right.y);
      double diff = calculateDelta(p1, p2);
      if (diff <= traversal->tol) {
        traversal->add(right);
      } 
    }

    if (within_bounds_down && !found_down) {
      HSLAPixel p1 = traversal->png_.getPixel(traversal->startPoint.x, traversal->startPoint.y);
      HSLAPixel p2 = traversal->png_.getPixel(down.x, down.y);
      double diff = calculateDelta(p1, p2);
      if (diff <= traversal->tol) {
        traversal->add(down);
      } 
    }

    if (within_bounds_left && !found_left) {
      HSLAPixel p1 = traversal->png_.getPixel(traversal->startPoint.x, traversal->startPoint.y);
      HSLAPixel p2 = traversal->png_.getPixel(left.x, left.y);
      double diff = calculateDelta(p1, p2);
      if (diff <= traversal->tol) {
        traversal->add(left);
      } 
    }

    if (within_bounds_up && !found_up) {
      HSLAPixel p1 = traversal->png_.getPixel(traversal->startPoint.x, traversal->startPoint.y);
      HSLAPixel p2 = traversal->png_.getPixel(up.x, up.y);
      double diff = calculateDelta(p1, p2);
      if (diff <= traversal->tol) {
        traversal->add(up);
      } 
    }

  current = traversal->peek();
  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  return current;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  /*
  bool thisEmpty = false;
  bool otherEmpty = false;

  if (traversal == NULL) {
    thisEmpty = true;
  }
  if (other.traversal == NULL) {
    otherEmpty = true;
  }
  if (!thisEmpty) {
    thisEmpty = traversal -> empty();
  }
  if (!otherEmpty) {
    otherEmpty = other.traversal -> empty();
  }
  if (thisEmpty && otherEmpty) {
    return false;
  } else if (!thisEmpty && !otherEmpty) {
    return (traversal != other.traversal);
  } else return true;
  */
  return !(traversal != other.traversal && current == other.current);

}

