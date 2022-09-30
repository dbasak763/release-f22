/**
 * @file BFS.h
 */

#pragma once

#include <iterator>
#include <cmath>
#include <list>
#include <queue>
#include <algorithm>

#include "cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

using namespace cs225;

/**
 * A breadth-first ImageTraversal.
 * Derived from base class ImageTraversal
 */
class BFS : public ImageTraversal {
public:
  BFS(const PNG & png, const Point & start, double tolerance);
  double getDelta(const HSLAPixel & p1, const HSLAPixel & p2);
  ImageTraversal::Iterator begin();
  ImageTraversal::Iterator end();

  void add(const Point & point);
  Point pop();
  Point peek() const;
  bool empty() const;

private:
  /** @todo [Part 1] */
  /** add private members here*/
  const PNG & png;
  unsigned int width_;
  unsigned int height_;
  const Point & startPoint;
  double tol;
  std::list<Point> visitedPoints;
  ImageTraversal::Iterator current;
  ImageTraversal::Iterator startIterator;
  std::queue<Point> ImageTraversal;
};
