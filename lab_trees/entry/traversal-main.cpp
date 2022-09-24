#include <algorithm>
#include <iostream>
#include "binarytree.h"
#include "InorderTraversal.h"
#include "PreorderTraversal.h"

using namespace std;

int main() {
    // For deterministic behavior, use a fixed seed instead of a random device
    /*
    std::random_device r;
    std::mt19937 rng(r());
    std::cout << "Hi" << std::endl;
    BinaryTree<int> myTree;
    for (int i = 1; i <= 10; i++)
        myTree.insertRandom(i, rng);
    myTree.print();


    PreorderTraversal<int> pot(myTree.getRoot());
    cout<<"Preorder Traversal: ";
    for (TreeTraversal<int>::Iterator it = pot.begin(); it != pot.end(); ++it) {
        cout<<(*it)->elem<<" ";
    }
    cout<<endl;
    std::cout << "Hi" << std::endl;
    //problem with inordertraversal
    InorderTraversal<int> iot(myTree.getRoot());
    cout<<"Inorder Traversal:  ";
    for (TreeTraversal<int>::Iterator it = iot.begin(); it != iot.end(); ++it) {
        cout<<(*it)->elem<<" ";
    }
    cout<<endl;
    */
    BinaryTree<int> treeLeft(genNonIsOrderedTreeLeft());

    std::cout << (treeLeft.isOrderedIterative() == false) << std::endl;

    BinaryTree<int> treeRight(genNonIsOrderedTreeRight());

    std::cout << (treeRight.isOrderedIterative() == false) << std::endl;

    BinaryTree<int> tree2;
    genIsOrderedTree(tree2);

    std::cout << (tree2.isOrderedIterative() == true) << std::endl;

}
