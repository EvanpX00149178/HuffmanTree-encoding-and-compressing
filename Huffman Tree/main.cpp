using namespace std;
#include <iostream>
#include <string>
#include <unordered_map>
#include "HuffmanTree.h"
#include <fstream>
#include <iostream>
#include "Compare.h"
#include <vector>
#include <bitset>
#include <streambuf>
#include <sstream>

//Gives frequency of each character in a text file.


unordered_map<int, int> printFrequency(ifstream&, string&);

int main()
{

    priority_queue<HuffmanTreeNode* ,vector<HuffmanTreeNode*>, Compare> trees;


    string originalMessage;
    unordered_map<int, int> CharFreqMap;

    ifstream inputFile("input.txt", std::ios::binary);

    

    //Task 1
    CharFreqMap = printFrequency(inputFile,originalMessage);
    


    for (auto& it : CharFreqMap) {
         trees.push(new HuffmanTreeNode(it.first, it.second));
    }
    trees.push(new HuffmanTreeNode(256, 1)); // Adding pseudo EOF

    //Task 2
    HuffmanTree tree = HuffmanTree(trees); //BuildsTree

    //Task 3
    unordered_map<int, string> encodedTree;
    tree.mapEncodeChar(encodedTree); //Maps each char to string of 0,1's

    //Task 4
    ofstream encodedOutput("encoded.txt", std::ios::binary);
    tree.encodeToFile(encodedTree, encodedOutput, originalMessage); //encodes the text to string of 0,1's using the map writes to encoded file.
    encodedOutput.close();


    ifstream encodedInput("encoded.txt", std::ios::binary);
    string encodedFile,inputToBeCompressed;

    ostringstream buffer2;
    buffer2 << encodedInput.rdbuf();																							
    encodedFile.assign(buffer2.str());                   //Reads in encoded file of 0,1's
    inputToBeCompressed = encodedFile;


    //Task 5
    ofstream decodedOutput("decoded.txt", std::ios::binary);
    tree.decodeToFile(encodedFile,decodedOutput); //Decodes the file of 0,1's back to readable file.
    decodedOutput.close();


    //Task 6 Including embedding Huffman Tree as the first bytes
    ofstream compressedFile("compressed.txt", std::ios::binary);
    tree.compressString(inputToBeCompressed, compressedFile); //Compresses the string of 0,1's to characters of 8 bit chunks and stores it in a file.
    compressedFile.close();



    //Task 7
    ifstream filetodecompress("compressed.txt", std::ios::binary);
    ofstream filetowriteto("decompressed.txt", std::ios::binary);
    tree.decompressString(filetodecompress, filetowriteto); //Decompresses the characters of 8 bit chunks and writes the string of 0,1's to a file
    filetodecompress.close();
    filetowriteto.close();

    string decompressedFile;
    ifstream decompressedInput("decompressed.txt", std::ios::binary);


    ostringstream buffer3;
    buffer3 << decompressedInput.rdbuf();																							
    decompressedFile.assign(buffer3.str());                   //Reads in encoded file of 0,1's


    decompressedInput.close();


    //Proof the final text is the same as the original
    ofstream finalOutput("final.txt", std::ios::binary);
    tree.decodeToFile(decompressedFile, finalOutput); // Decodes the recently decompressed string of 0,1's to ensure the final text matches the original text taken in.
    finalOutput.close();

    
    
    

   
}


unordered_map<int, int> printFrequency(ifstream& input, string& originalMessage)
{


    /***************************************************************************************
    *    Usage: Modified & Used
    *    Title: Frequency of each character in a String using unordered_map in C++
    *    Author: Geeks4Geeks
    *	 Date last updated: 26 Oct, 2020
    *    Availability: https://www.geeksforgeeks.org/frequency-of-each-character-in-a-string-using-unordered_map-in-c/
    *    Accessed on: 24 April 2021
    *
    ***************************************************************************************/
    ostringstream buffer;
    buffer << input.rdbuf();
    originalMessage.assign(buffer.str());




    // Define an unordered_map
    unordered_map<int, int> M;

    // Traverse string str check if
    // current character is present
    // or not
    for (int i = 0; originalMessage[i]; i++)
    {
        // If the current characters
        // is not found then insert
        // current characters with
        // frequency 1
        if (M.find(originalMessage[i]) == M.end())
        {
            M.insert(make_pair(int(originalMessage[i]), 1));
        }

        // Else update the frequency
        else
        {
            M[originalMessage[i]]++;
        }
    }

    // Traverse the map to print the
    // frequency
    return M;
}

