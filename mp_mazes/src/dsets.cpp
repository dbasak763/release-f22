/* Your code here! */
#include "dsets.h"
//adding n unconnected root nodes
void DisjointSets::addelements(int num) {
    for (int i = 0; i < num; i++) {
        par.push_back(-1);
    }
}

int DisjointSets::find(int elem) {
    if (par[elem] < 0) {
        return elem;
    }
    int result = find(par[elem]);

    par[elem] = result;

    return result;
}

void DisjointSets::setunion(int a, int b) {
    int root_a = find(a);
    int root_b = find(b);

    if (root_a == root_b) return;

    int size_a = size(root_a);
    int size_b = size(root_b);

    if (size_a == size_b) {
        par[root_a] += par[root_b];
        par[root_b] = root_a; 
    } else if (size_a < size_b) {
        par[root_b] += par[root_a];
        par[root_a] = root_b;
    } else {
        par[root_a] += par[root_b];
        par[root_b] = root_a;
    }
    /*
    for (unsigned i = 0; i < par.size(); i++) {
        std::cout << par[i] << " ";
    }
    std::cout << std::endl;
    */
}

int DisjointSets::size(int elem) {
    int root = find(elem);
    return -par[root];
}