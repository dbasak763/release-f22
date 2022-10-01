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
   for (int i = 0; i < 500; i++) {
     for (int j = 0; j < 500; j++) {
       visited[i][j] = 0;
     }
   }
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
    if (!traversal->empty()) {
        Point point = traversal->pop();
        visited[point.x][point.y] = 1;
        while(!traversal->empty() && visited[traversal->peek().x][traversal->peek().y]) {
          traversal->pop();
        }
        std::cout << "Popped " << point << std::endl;
        Point up = Point(point.x, point.y - 1);
        Point down = Point(point.x, point.y + 1);
        Point left = Point(point.x - 1, point.y);
        Point right = Point(point.x + 1, point.y);

        bool found_left = visited[left.x][left.y];
        bool found_right = visited[right.x][right.y];
        bool found_up = visited[up.x][up.y];
        bool found_down = visited[down.x][down.y];

        bool within_bounds_left = (left.x >= 0 && left.x < traversal->width_ && left.y >= 0 && left.y < traversal->height_);
        bool within_bounds_right = (right.x >= 0 && right.x < traversal->width_ && right.y >= 0 && right.y < traversal->height_);
        bool within_bounds_up = (up.x >= 0 && up.x < traversal->width_ && up.y >= 0 && up.y < traversal->height_);
    bool within_bounds_down = (down.x >= 0 && down.x < traversal->width_ && down.y >= 0 && down.y < traversal->height_); 

    if (within_bounds_right && !found_right) {
      HSLAPixel p1 = traversal->png_.getPixel(traversal->startPoint.x, traversal->startPoint.y);
      HSLAPixel p2 = traversal->png_.getPixel(right.x, right.y);
      double diff = calculateDelta(p1, p2);
      if (diff < traversal->tol) {
        traversal->add(right);
        std::cout << "Added point on right of " << point << ": " << right << std::endl;
      } 
    }

    if (within_bounds_down && !found_down) {
      HSLAPixel p1 = traversal->png_.getPixel(traversal->startPoint.x, traversal->startPoint.y);
      HSLAPixel p2 = traversal->png_.getPixel(down.x, down.y);
      double diff = calculateDelta(p1, p2);
      if (diff < traversal->tol) {
        traversal->add(down);
        std::cout << "Added point on down of " << point << ": " << down << std::endl;
      } 
    }

    if (within_bounds_left && !found_left) {
      HSLAPixel p1 = traversal->png_.getPixel(traversal->startPoint.x, traversal->startPoint.y);
      HSLAPixel p2 = traversal->png_.getPixel(left.x, left.y);
      double diff = calculateDelta(p1, p2);
      if (diff < traversal->tol) {
        traversal->add(left);
        std::cout << "Added point on left of " << point << ": " << left << std::endl;
      } 
    }

    if (within_bounds_up && !found_up) {
      HSLAPixel p1 = traversal->png_.getPixel(traversal->startPoint.x, traversal->startPoint.y);
      HSLAPixel p2 = traversal->png_.getPixel(up.x, up.y);
      double diff = calculateDelta(p1, p2);
      if (diff < traversal->tol) {
        traversal->add(up);
        std::cout << "Added point on up of " << point << ": " << up << std::endl;
      } 
    }

    if (!traversal->empty()) current = traversal->peek();
    }
    
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
  //std::cout << "Hi" << std::endl;
  if (traversal == other.traversal) {
    return !(current.x == other.current.x && current.y == other.current.y);
  }
  if (traversal != other.traversal) {
    if (other.traversal == NULL) {
       //std::cout << "Hi" << std::endl;
       return !traversal -> empty();
    } else {
       return !(current.x == other.current.x && current.y == other.current.y);
    }
  }
  return false;

}

