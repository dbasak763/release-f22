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
DFS::DFS(const PNG & png, const Point & start, double tolerance) : startPoint(start) {  
  tol = tolerance;
  width_ = png.width();
  height_ = png.height();

  *current = start;
  startIterator = current;
 
  ImageTraversal.push(*current);

  while (!empty()) {
    Point point = pop();
    *current = point;
    visitedPoints.push_back(point);
    Point left = Point(point.x, point.y - 1);
    Point right = Point(point.x, point.y + 1);
    Point up = Point(point.x - 1, point.y);
    Point down = Point(point.x + 1, point.y);

    bool found_left = (std::find(visitedPoints.begin(), visitedPoints.end(), left) != visitedPoints.end());
    bool found_right = (std::find(visitedPoints.begin(), visitedPoints.end(), right) != visitedPoints.end());
    bool found_up = (std::find(visitedPoints.begin(), visitedPoints.end(), up) != visitedPoints.end());
    bool found_down = (std::find(visitedPoints.begin(), visitedPoints.end(), down) != visitedPoints.end());

    bool within_bounds_left = (left.x >= 0 && left.x < height_ && left.y >= 0 && left.y < width_);
    bool within_bounds_right = (right.x >= 0 && right.x < height_ && right.y >= 0 && right.y < width_);
    bool within_bounds_up = (up.x >= 0 && up.x < height_ && up.y >= 0 && up.y < width_);
    bool within_bounds_down = (down.x >= 0 && down.x < height_ && down.y >= 0 && down.y < width_); 

    if (within_bounds_left && !found_left) {
      HSLAPixel p1 = png.getPixel(startPoint.x, startPoint.y);
      HSLAPixel p2 = png.getPixel(left.x, left.y);
      double diff = getDelta(p1, p2);
      if (diff <= tol) {
        ImageTraversal.push(left);
      } 
    }

    if (within_bounds_right && !found_right) {
      HSLAPixel p1 = png.getPixel(startPoint.x, startPoint.y);
      HSLAPixel p2 = png.getPixel(right.x, right.y);
      double diff = getDelta(p1, p2);
      if (diff <= tol) {
        ImageTraversal.push(right);
      } 
    }

    if (within_bounds_up && !found_up) {
      HSLAPixel p1 = png.getPixel(startPoint.x, startPoint.y);
      HSLAPixel p2 = png.getPixel(up.x, up.y);
      double diff = getDelta(p1, p2);
      if (diff <= tol) {
        ImageTraversal.push(up);
      } 
    }

    if (within_bounds_down && !found_down) {
      HSLAPixel p1 = png.getPixel(startPoint.x, startPoint.y);
      HSLAPixel p2 = png.getPixel(down.x, down.y);
      double diff = getDelta(p1, p2);
      if (diff <= tol) {
        ImageTraversal.push(down);
      } 
    }
  }

}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  ImageTraversal.push(point);
  return;
}

double DFS::getDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
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
ImageTraversal::Iterator DFS::begin() {
  return ImageTraversal::Iterator(startIterator);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  return ImageTraversal::Iterator();
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
