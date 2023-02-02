#include "HuffmanTreeNode.h"

HuffmanTreeNode::HuffmanTreeNode(int character, int frequency)
{
    data = character;
    freq = frequency;
    left = right = nullptr;
}
