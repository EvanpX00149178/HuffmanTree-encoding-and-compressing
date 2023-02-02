using namespace std;
#include "HuffmanTree.h"
#include <fstream>
#include <iostream>
#include "Compare.h"
#include <bitset>
#include <sstream>
#include <streambuf>

HuffmanTree::HuffmanTree(priority_queue<HuffmanTreeNode*, vector<HuffmanTreeNode*>, Compare> queue)
{
	while (queue.size() >=2) {
		HuffmanTreeNode* newNode;

		HuffmanTreeNode* newNodeLeft = queue.top();
		queue.pop();

		HuffmanTreeNode* newNodeRight = queue.top();
		queue.pop();

		newNode = new HuffmanTreeNode(0, (newNodeLeft->freq + newNodeRight->freq));
		newNode->left = newNodeLeft;
		newNode->right = newNodeRight;

		queue.push(newNode);
	}
	root = queue.top();
	weight = root->freq;
}

void HuffmanTree::mapEncodeChar(HuffmanTreeNode* temp, string encoding, unordered_map<int, string> &encoded)
{
		if (temp->data) {
			encoded.insert(make_pair(temp->data, encoding)); // pairs the character with the string of 0,1's to access it in the tree
			return;
		}
		if (temp->left) {
			mapEncodeChar(temp->left, encoding+"0", encoded);
		}
		if (temp->right) {
			mapEncodeChar(temp->right, encoding+"1", encoded);
		}

		
	
}

void HuffmanTree::mapEncodeChar(unordered_map<int, string>& m)
{
	string s;
	mapEncodeChar(root, s, m);
}

void HuffmanTree::encodeToFile(unordered_map<int, string>& encoded, ofstream& OutFile, string line)
{
	if (OutFile.is_open()) {
		for (int i = 0; i < line.size(); i++)
		{
			OutFile << encoded[line[i]]; //Takes the character at line[i] and uses the map of chars and strings to take the appropriate 0,1's to encode it.
		}
		OutFile << encoded[256];
	}
}

void HuffmanTree::decodeToFile(string& input, ofstream& OutFile)
{
	string text;
	decodeToFile(input, root, text);

	if (OutFile.is_open()) {
		OutFile << text;
	}
}

void HuffmanTree::compressString(string& encodedinput, ofstream& OutFile)
{
	
	string chunk, compressed, encodedTree, tobeCompressed;
	unsigned long long decimal;
	

	encodedTree = encodeHuffmanTree();
	
	string encodedTreeSize= bitset<32> (encodedTree.size()).to_string();

	tobeCompressed = encodedTreeSize+encodedTree+encodedinput;



	while (tobeCompressed.size() > 0)
	{

		if (tobeCompressed.size() >= 8)
		{
			chunk = tobeCompressed.substr(0, 8);				//compresses 8 bit chunks at a time to a character and adds that char.
			tobeCompressed.erase(0, 8);
			decimal = bitset<8>(chunk).to_ullong();
			compressed += char(decimal);
		}

		else                                                    //if not enough bits add 0,s to the end till it equals to an 8 bit chunk and store it.
		{
			int j = 8 - tobeCompressed.size();
			for (int i = 0; i < j; i++)
			{
				tobeCompressed += '0';
			}

			decimal = bitset<8>(tobeCompressed).to_ullong();
			compressed += char(decimal);
			tobeCompressed.erase(0, tobeCompressed.size());
		}

	}

	OutFile << compressed;


}

void HuffmanTree::decompressString(ifstream& input, ofstream& OutFile)
{
	
	string decompressed;
	string start;


	ostringstream buffer;
	buffer << input.rdbuf();																							
	start.assign(buffer.str());
	
	



	for (int i = 0; i < start.size(); i++)
	{
		decompressed.append(bitset<8>(start[i]).to_string());
	}


	bitset<32> bitsUsedforSize;
	stringstream treeSize(decompressed.substr(0, 32));
	treeSize >> bitsUsedforSize;
	unsigned int bitsUsedforTree = bitsUsedforSize.to_ulong();


	string encodedString = decompressed.substr(bitsUsedforTree + 32, decompressed.size() - (bitsUsedforTree + 32));
	string encodedTree = decompressed.substr(32, bitsUsedforTree);

	OutFile << encodedString;
}

string HuffmanTree::encodeHuffmanTree()
{
	
	string input;
	encodeHuffmanTree(root, input);
	return input;
}

string HuffmanTree::encodeHuffmanTree(HuffmanTreeNode* temp, string& input)
{
	//Encoding in pre order traversal


	if (temp != nullptr) {

		
		if (temp->data != 0)
			input.append("1" + bitset<8>(temp->data).to_string());
		else
			input.append("0");
		
		encodeHuffmanTree(temp->left, input);
		encodeHuffmanTree(temp->right, input);
																					
	}

	return input;
}

void HuffmanTree::decodeToFile(string& input, HuffmanTreeNode* temp, string& toOutFile)
{



	for (int i = 0; i <= input.size(); i++)
	{

		if (temp->data == 256) {
			break;						//if you reach EOF break.
		}

		if (temp->data) {
			toOutFile += char(temp->data);//If leaf node is reached make it a char and add it to the string for the outfile.
			temp = root;	//reset to traverse again.
			i--;
		}
		else if (input[i] == '0' && temp->left) {
			temp = temp->left;				// if  not leaf node and the encoded input says to go left, go left.
		}
		else if (input[i] == '1' && temp->right) {
			temp = temp->right;	// if  not leaf node and the encoded input says to go right, go right.
		}
	}

	//Attempted recursively first
	/*if (temp->data) {

		toOutFile += temp->data;
		return;

	}
	else {
		if (temp->left && line[0] == '0') {
			line.erase(line.begin());
			decodeToFile(line, temp->left, toOutFile);

		}
		else if(temp->right && line[0] == '1') {
			line.erase(line.begin());
			decodeToFile(line, temp->right, toOutFile);
		}
	}*/
	

		
	
	
}
