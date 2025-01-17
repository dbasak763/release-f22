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
BFS::BFS(const PNG & png, const Point & start, double tolerance) {  
  startPoint = start;
  tol = tolerance;
  png_ = png;
  width_ = png.width();
  height_ = png.height();

  add(startPoint);
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
  queue.push(point);
  return;
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
  return ImageTraversal::Iterator(this, startPoint);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  return ImageTraversal::Iterator();
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
  Point toBeRemoved = queue.front();
  queue.pop();
  return toBeRemoved;
}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const {
  return queue.front();
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
  return queue.empty();
}
