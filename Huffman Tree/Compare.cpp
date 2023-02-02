#include "Compare.h"



bool Compare::operator()(HuffmanTreeNode* lhs, HuffmanTreeNode* rhs)
{
	return lhs->freq > rhs->freq;
}
