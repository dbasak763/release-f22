#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"

/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * 
 * @param png The image this DFS is going to traverse
 * @param start The start point of this DFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this DFS
 */
DFS::DFS(const PNG & png, const Point & start, double tolerance) {  
  png = png;
  startPoint = start;
  tolerance = tolerance;
  width_ = png.width();
  height_ = png.height();
  
  *current = start;
  *startIterator = start;
  visitedPoints.insert(*current);
  add(*current);

  Point left = new Point(start.x, start.y - 1);
  Point right = new Point(start.x, start.y + 1);
  Point up = new Point(start.x - 1, start.y);
  Point down = new Point(start.x + 1, start.y);

  add(right);
  add(down);
  add(left);
  add(up);

  while (!empty()) {
    Point point = pop();
    if (!empty()) {
      *current = point;
      visitedPoints.insert(*current);
      Point left = new Point(*current.x, *current.y - 1);
      Point right = new Point(*current.x, *current.y + 1);
      Point up = new Point(*current.x - 1, *current.y);
      Point down = new Point(*current.x + 1, *current.y);
      
      add(right);
      add(down);
      add(left);
      add(up);
    }

  }

}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  return ImageTraversal::Iterator(startIterator);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  return ImageTraversal::Iterator(NULL);
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  
  if (point.x >= 0 && point.x < height_ 
  && point.y >= 0 && point.y < width_) {
    double diff = calculateDelta(png.getPixel(startPoint.x, startPoint.y), png.getPixel(point.x, point.y));
    if (diff <= tolerance) {
      ImageTraversal.push(point);
    }
  }
  return;
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
  Point toBeRemoved = ImageTraversal.top();
  ImageTraversal.pop();
  return toBeRemoved;
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const {
  return ImageTraversal.top();
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  return (ImageTraversal.empty());
}
