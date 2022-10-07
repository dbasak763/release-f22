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
    Node* r = t->right;
    Node* temp = r->left;

    r->left = t;
    t->right = temp;
    t = r;

    t->height = std::max(heightOrNeg1(t->left), heightOrNeg1(t->right)) + 1;
    r->height = std::max(heightOrNeg1(r->left), heightOrNeg1(r->right)) + 1;
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

    Node* l = t->left;
    Node* temp = l->right;

    l->right = t;
    t->left = temp;
    t = l;

    t->height = std::max(heightOrNeg1(t->left), heightOrNeg1(t->right)) + 1;
    l->height = std::max(heightOrNeg1(l->left), heightOrNeg1(l->right)) + 1;
    
}
template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    rotateRight(t->right);
    rotateLeft(t);

}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    int diff = heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);
    if (diff == -2) {
        int l_diff = heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left);
        if (l_diff == -1) {
            rotateRight(subtree);
        } else {
            rotateLeftRight(subtree);
        }
    } else if (diff == 2) {
        int r_diff = heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left);
        if (r_diff == 1) {
            rotateLeft(subtree);
        } else {
            rotateRightLeft(subtree);
        }
    }
    subtree->height = std::max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right)) + 1;
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
        rebalance(subtree);
    } else if (key > subtree->key) {
        remove(subtree->right, key);
        rebalance(subtree);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            delete subtree;
            subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            Node* maxNode = subtree->left;
            while (maxNode->right != NULL) {
                maxNode = maxNode->right;
            }
            swap(subtree, maxNode);
            remove(subtree->left, key);
            //rebalance(subtree);
        } else {
            /* one-child remove */
            if (subtree->left == NULL) {
                Node* temp = subtree->right;
                delete subtree;
                subtree = temp; 
            } else if (subtree->right == NULL) {
                Node* temp = subtree->left;
                delete subtree;
                subtree = temp; 
            }
        }
        // your code here
        
    }
}
