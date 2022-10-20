/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <math.h>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
     if (first[curDim] == second[curDim]) {
       return (first < second);
     }
    return (first[curDim] < second[curDim]);
} //works

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
     double dist_To_currBest_squared = 0.0;
     double dist_To_potential_squared = 0.0;

     for (int i = 0; i < Dim; i++) {
       dist_To_currBest_squared += (target[i] - currentBest[i]) * (target[i] - currentBest[i]);
       dist_To_potential_squared += (target[i] - potential[i]) * (target[i] - potential[i]);
     }
     if (dist_To_potential_squared == dist_To_currBest_squared) {
       return (potential < currentBest);
     }
     return (dist_To_potential_squared < dist_To_currBest_squared);
} //works

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    size = newPoints.size();
    root = NULL;
    if (newPoints.empty()) {
       return;
    }
    vector<Point<Dim>> points;
    for (unsigned i = 0; i < newPoints.size(); i++) {
      points.push_back(newPoints[i]);
    }
    //deletion(root);
    std::cout << "Before Building Tree" << std::endl;
    BuildTree(points, 0, 0, newPoints.size() - 1, root); //doesn't work
    std::cout << "After Building Tree" << std::endl;
    if (root == NULL) std::cout << "root is NULL after building tree" << std::endl;
    std::cout << "RootNode: " << root->point << std::endl;

}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
   size = other->size;
   assign(other->root);
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
   size = rhs->size;
   assign(rhs->root);

   return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  size = 0;
  deletion(root);

}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    return findNearestNeighbor(query, 0, root);
}

template <int Dim>
Point<Dim> KDTree<Dim>::getMedian(vector<Point<Dim>> newPoints) {
  return newPoints[(newPoints.size() - 1) / 2];
}

template <int Dim>
int KDTree<Dim>::partition(vector<Point<Dim>>& list, int left, int right, int pivotIndex, int dim) {
  Point<Dim> pivotValue = list[pivotIndex];
  swap(list[pivotIndex], list[right]);
  int storeIndex = left;
  for (int i = left; i < right; i++) {
    bool smaller = smallerDimVal(list[i], pivotValue, dim);
    if (smaller) {
      swap(list[storeIndex], list[i]);
      storeIndex++;
    }
  }
  swap(list[right], list[storeIndex]);
  return storeIndex;
} //exactly matching

template <int Dim>
Point<Dim> KDTree<Dim>::select(vector<Point<Dim>>& list, int left, int right, int k, int dim) {
  int pivotIndex = k;
  while (true) {
    if (left == right) {
      return list[left];
    }
    //std::cout << "Before Partition" << std::endl;
    pivotIndex = (left + right) / 2;
    pivotIndex = partition(list, left, right, pivotIndex, dim); //not sure if works properly but compiles
    //std::cout << "After Partition" << std::endl;
    if (k == pivotIndex) {
      //std::cout << "Select outputs a point" << std::endl;
      return list[k];
    } else if (k < pivotIndex){
      right = pivotIndex - 1;
    } else {
      left = pivotIndex + 1;
    }
    //std::cout << "End of iteration select" << std::endl;
  }
} //exactly matching

template <int Dim>
void KDTree<Dim>::BuildTree(vector<Point<Dim>>& newPoints, int dim, int left, int right, KDTreeNode *& currRoot) {
  if (left <= right) {
    int mid = (left + right) / 2;
    //std::cout << "Before Select" << std::endl;
    const Point<Dim> &point = select(newPoints, left, right, mid, dim);
    //std::cout << "Hi" << std::endl;
    currRoot = new KDTreeNode(point); 
    //std::cout << "After Select" << std::endl;
    std::cout << "CurrRoot = " << currRoot->point << std::endl;
    BuildTree(newPoints, (dim + 1) % Dim, left, mid - 1, currRoot->left);
    BuildTree(newPoints, (dim + 1) % Dim, mid + 1, right, currRoot->right);
  }
}


template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query, int dim, KDTreeNode * currRoot) const {
  if (currRoot == NULL) {
    return Point<Dim> ();
  }
  if (currRoot->left == NULL && currRoot->right == NULL) {
    return currRoot->point;
  }
  Point<Dim> nearest, tempNearest;

  bool RecursedOnLeftSubtree;

  if (query[dim] < currRoot->point[dim]) {
    nearest = findNearestNeighbor(query, dim, currRoot->left);
    RecursedOnLeftSubtree = true;
  } else {
    nearest = findNearestNeighbor(query, dim, currRoot->right);
    RecursedOnLeftSubtree = false;
  }

  if (shouldReplace(query, nearest, currRoot->point)) {
    nearest = currRoot->point;
  }

  double radius = 0.0;

  for (int i = 0; i < Dim; i++) {
    double diff = query[i] - nearest[i];
    radius += diff * diff;
  }
  double diff = currRoot->point[dim] - query[dim];
  double splitDist = diff * diff;

  if (radius >= splitDist) {
     if (RecursedOnLeftSubtree) {
       tempNearest = findNearestNeighbor(query, dim, currRoot->right);
     } else {
       tempNearest = findNearestNeighbor(query, dim, currRoot->left);
     }
     if (shouldReplace(query, nearest, tempNearest)) {
       nearest = tempNearest;
     }
  }

  return nearest;

}

template <int Dim>
void KDTree<Dim>::assign(KDTreeNode* currRoot) {
  if (currRoot == NULL) return;
  for (int i = 0; i < Dim; i++) {
     *root->point[i] = *currRoot->point[i];
  }
  *root->left = assign(*currRoot->left);
  *root->right = assign(*currRoot->right);
}

template <int Dim>
void KDTree<Dim>::deletion(KDTreeNode* currRoot) {
  if (currRoot == NULL) return;
  KDTreeNode* left_ = currRoot->left;
  KDTreeNode* right_ = currRoot->right;

  delete currRoot;
  currRoot = NULL;

  deletion(left_);
  deletion(right_);

}

