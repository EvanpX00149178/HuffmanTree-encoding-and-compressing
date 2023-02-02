#pragma once
#include "HuffmanTreeNode.h"
#include <string>
#include <vector>
#include <unordered_map>
class HuffmanTree
{
public:
	HuffmanTree(priority_queue<HuffmanTreeNode*, vector<HuffmanTreeNode*>, Compare> queue);
	void mapEncodeChar( unordered_map<int, string>&);
	void encodeToFile(unordered_map<int, string>&, ofstream& OutFile, string);
	void decodeToFile(string& line, ofstream& OutFile);
	void compressString(string&, ofstream& OutFile);
	void decompressString(ifstream& input, ofstream& OutFile);
	string encodeHuffmanTree();
	

private:
	string encodeHuffmanTree(HuffmanTreeNode*, string&);
	void mapEncodeChar(HuffmanTreeNode*, string, unordered_map<int, string>&);
	void decodeToFile(string& InFile, HuffmanTreeNode*, string& toOutFile);
	HuffmanTreeNode* root;
	int weight;
	
};

