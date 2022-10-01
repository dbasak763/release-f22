/**
 * @file bst.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V BST<K, V>::find(const K& key)
{
    Node* searchNode = find(root, key);
    if (searchNode == NULL) {
        return V();
    }
    return searchNode -> value;
}

template <class K, class V>
struct BST<K, V>::Node* & BST<K, V>::find(Node* & subtree, const K& key)
{
    if (subtree == NULL || subtree->key == key) {
        return subtree;
    }
    if (subtree->key > key) {
        return find(subtree->left, key);
    }
    return find(subtree->right, key);
}

template <class K, class V>
void BST<K, V>::insert(const K & key, const V & value)
{
   insert(root, key, value);
}

template <class K, class V>
void BST<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
   Node*& curr = find(subtree, key);
   if (curr == NULL) curr = new Node(key, value);

}

template <class K, class V>
void BST<K, V>::swap(Node*& first, Node*& second)
{
    if (first == NULL || second == NULL) {
        Node* temp = first;
        first = second;
        second = temp;
    } else {
        K temp_key = first->key;
        V temp_value = first->value;
        first->key = second->key;
        first->value = second->value;
        second->key = temp_key;
        second->value = temp_value;
    }
}

template <class K, class V>
void BST<K, V>::swapR(Node*& subtree, Node*& first, Node*& second) {
    if (root == NULL) return;
    Node* left = subtree->left;
    Node* right = subtree->right;

    if (left == first || left == second) {
        subtree->left = second;
    } else {
        return swapR(left, first, second);
    }

    if (right == first || right == second) {
        subtree -> right = first;
    } else {
        return swapR(right, first, second);
    }
}

template <class K, class V>
void BST<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void BST<K, V>::remove(Node*& subtree, const K& key)
{
    Node*& node = find(subtree, key);
    if (node == NULL) return;
    if (node->left == NULL && node->right == NULL) { //0 children
        node = NULL;
    } else if (node->right == NULL) { //1 child
        Node* temp = node->left;
        node = temp;
    } else if (node->left == NULL) { //1 child
        Node* temp = node->right;
        node = temp;
    } else { //2 children
        Node* max_node = maxNode(node->left);
        node->key = max_node->key;
        node->value = max_node->value;
        remove(node->left, max_node->key);
    }
}

template <class K, class V>
struct BST<K, V>::Node* & BST<K, V>::removeR(Node*& subtree, const K& key) {
    if (subtree == NULL) return subtree;

    if (subtree->key < key) {
        subtree->right = removeR(subtree->right, key);
    } else if (subtree->key > key) {
        subtree->left = removeR(subtree->left, key);
    } else {
        if (subtree -> left == NULL && subtree -> right == NULL) {
            Node* temp = NULL;
            delete subtree;
        } else if (subtree -> left == NULL) {
            Node* temp = subtree -> right;
            delete subtree;
            return temp;
        } else if (subtree -> right == NULL) {
            Node* temp = subtree -> left;
            delete subtree;
            return temp;
        }
        Node* temp = minNode(subtree->right);
        subtree->key = temp->key;
        subtree->value = temp->value;
        subtree->right = removeR(subtree->right, temp->key);
    }
    return subtree;

}

template <class K, class V>
struct BST<K, V>::Node* &  BST<K, V>::maxNode(Node*& root) {
    if (root->right == NULL) return root;
    return maxNode(root->right);
}

template <class K, class V>
BST<K, V> listBuild(std::vector<std::pair<K, V>> inList){
    BST<K, V> bst = BST<K, V>();
    
    for (unsigned i = 0; i < inList.size(); i++) {
        bst.insert(inList[i].first, inList[i].second);
    }
    return bst;
    
}

template <class K, class V>
std::vector<int> allBuild(std::vector<std::pair<K, V>> inList){
    std::vector<int> histogram(inList.size());
    std::sort(inList.begin(), inList.end());
    do {
        BST<K, V> formed_BST = listBuild(inList); //null
        int formed_BST_height = formed_BST.height();
        //std::cout << formed_BST_height << std::endl;
        histogram.at(formed_BST_height) += 1;
    } while (std::next_permutation(inList.begin(), inList.end()));
    return histogram;
}