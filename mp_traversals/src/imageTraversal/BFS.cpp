#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace cs225;

/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this BFS is going to traverse
 * @param start The start point of this BFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this BFS
 */
BFS::BFS(const PNG & png, const Point & start, double tolerance) : png(png), startPoint(start) {  
  tol = tolerance;
  width_ = png.width();
  height_ = png.height();
  
  *current = start;
  startIterator = current;
  visitedPoints.push_back(start);

  add(start);

  while (!empty()) {
    Point point = pop();
    
    *current = point;
    visitedPoints.push_back(point);
    Point left = Point(point.x, point.y - 1);
    Point right = Point(point.x, point.y + 1);
    Point up = Point(point.x - 1, point.y);
    Point down = Point(point.x + 1, point.y);
      
    add(right);
    add(down);
    add(left);
    add(up);
    

  }
}

double BFS::getDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator BFS::begin() {
  return ImageTraversal::Iterator(startIterator);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
  bool found = (std::find(visitedPoints.begin(), visitedPoints.end(), point) != visitedPoints.end());
  if (!found && point.x >= 0 && point.x < height_ 
  && point.y >= 0 && point.y < width_) {
    double diff = getDelta(png.getPixel(startPoint.x, startPoint.y), png.getPixel(point.x, point.y));
    if (diff <= tol) {
      ImageTraversal.push(point);
    }
  }
  return;
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
  Point toBeRemoved = ImageTraversal.front();
  ImageTraversal.pop();
  return toBeRemoved;
}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const {
  return ImageTraversal.front();
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
  return ImageTraversal.empty();
}
