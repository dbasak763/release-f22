/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node* r = t->right;
    Node* temp = r->left;

    r->left = t;
    t->right = temp;

    t->height = max(heightOrNeg1(t->left), heightOrNeg1(t->right)) + 1;
    r->height = max(heightOrNeg1(r->left), heightOrNeg1(r->right)) + 1;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node* l = t->left;
    Node* temp = l->right;

    l->right = t;
    t->left = temp;

    t->height = max(heightOrNeg1(t->left), heightOrNeg1(t->right)) + 1;
    l->height = max(heightOrNeg1(l->left), heightOrNeg1(l->right)) + 1;
    

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    if ((heightOrNeg1(subtree->left) - heightOrNeg1(subtree->right)) > 1) {
        if (heightOrNeg1(subtree->left->left) > heightOrNeg1(subtree->left->right)) {
            node = rotateRight(node);
        } else {
            node = rotateLeftRight(node);
        }
    } else {
        if (heightOrNeg1(subtree->right->right) > heightOrNeg1(subtree->right->left)) {
            node = rotateLeft(node);
        } else {
            node = rotateRightLeft(node);
        }
    }
    subtree->height = max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right)) + 1;
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if (subtree == NULL) {
        subtree = new Node(key, value);
    } else if (key < subtree->key) {
        insert(subtree->left, key, value);
    } else if (key > subtree->key) {
        insert(subtree->right, key, value);
    }
    rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        remove(subtree->left, key);
    } else if (key > subtree->key) {
        remove(subtree->right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            Node* maxNode = subtree->left;
            while (maxNode != NULL && maxNode->right != NULL) {
                maxNode = maxNode->right;
            }
            subtree->key = maxNode->key;
            subtree->value = maxNode->value;
            remove(subtree->left, maxNode->key);
        } else {
            /* one-child remove */
            if (subtree->left == NULL) {
                Node* temp = subtree -> right;
                subtree = temp; 
            } else if (subtree->right == NULL) {
                Node* temp = subtree -> left;
                subtree = temp;
            }
        }
        // your code here
    }
}
