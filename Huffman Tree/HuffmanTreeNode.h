#pragma once
using namespace std;
#include <queue>
class HuffmanTreeNode {
    friend class HuffmanTree;
    friend class Compare;
public:
    HuffmanTreeNode(int character, int frequency);
private:
    int data;
    int freq;
    HuffmanTreeNode* left;
    HuffmanTreeNode* right;
    
};

