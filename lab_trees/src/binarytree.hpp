/**
 * @file binarytree.hpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include "InorderTraversal.h"
#include <iostream>
#include <vector>

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + std::max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    std::cout << std::endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    std::cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
    template <typename T>
void BinaryTree<T>::mirror()
{
    //your code here
    mirror(root);
}
    template <typename T>
void BinaryTree<T>::mirror(Node*& root) {
    if (root == NULL) return;
    Node* temp = root -> left;
    root -> left = root -> right;
    root -> right = temp;
    mirror(root -> left);
    mirror(root -> right);
}

/**
 * isOrdered() function iterative version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedIterative() const
{
    // your code here
    InorderTraversal<T> iot(root);
    std::vector<T> vect;
    for (typename TreeTraversal<T>::Iterator it = iot.begin(); it != iot.end(); ++it) {
        vect.push_back((*it)->elem);
    }
    for (typename std::vector<T>::iterator it = vect.begin(); it != vect.end(); ++it) {
        if (++it == vect.end()) break;
        if (*(it) > *(++it)) return false;
    }
    return true;
}

/**
 * isOrdered() function recursive version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedRecursive() const
{
    return isOrderedRecursive(root);
}
template <typename T>
bool BinaryTree<T>::isOrderedRecursive(Node* root) const {
    if (root == NULL || (root -> left == NULL && root -> right == NULL)) {
        return true;
    }
    T root_data = root -> elem;

    if ((root -> left == NULL || root -> left -> elem <= root_data) && (root -> right == NULL || root_data <= root -> right -> elem)) {
        return isOrderedRecursive(root -> left) && isOrderedRecursive(root -> right);
    }
    return false;
}

