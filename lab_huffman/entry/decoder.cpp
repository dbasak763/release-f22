/**
 * @file decoder_prog.cpp
 * Decoder program for decoding files compressed with HuffmanTrees.
 */

#include "decoder.h"
#include "frequency.h"
#include "huffman_tree.h"

using namespace std;

int main(int argc, char** argv)
{
    vector<string> args(argv, argv + argc);
    return decoder::main(args);
    vector<Frequency> single;
    vector<Frequency> merge;
    for (int i = 1; i < 5; i++) {
        single.push_back(Frequency('a'+2*i, 2*i));
        merge.push_back(Frequency('a'+i, i));
    }
    Frequency expected1 = HuffmanTree::testRemoveSmallest(single, merge);
    std::cout << expected1.getFrequency() << std::endl;
    std::cout << merge[0].getFrequency() << std::endl;
    if (expected1 == merge[0]) std::cout << "True" << std::endl;
    single[0] = merge[0];
    Frequency expected2 = HuffmanTree::testRemoveSmallest(single, merge);
    if (expected2 == single[0]) std::cout << "True" << std::endl;

    return 0;
}
