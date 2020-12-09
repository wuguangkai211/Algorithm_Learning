#include <cstdio>
#include <iostream>

using namespace std;

template <class Type>
class Huffman
{
private:
    BinaryTree<int> tree;
    Type weight;

public:
    operator Type() const { return weight; }
    friend BinaryTree<int> HuffmanTree(Type[], int);
};



int main()
{

    return 0;
}
