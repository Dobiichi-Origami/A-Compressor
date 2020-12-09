//
// Created by TwinTails on 20/12/9.
//

#ifndef FINALE_TOOLS_HPP
#define FINALE_TOOLS_HPP

#include <cstring>
#include <fstream>
#include "../Header/HuffmanTreeNode.hpp"
#include "../Header/HuffmanTree.hpp"

using namespace std;

char *read(ifstream& in);
int* getFrequencyArray(ifstream &in);
int getSize(ifstream& in);
TreeNode* readAllFromFile(ifstream &in);
TreeNode* countTimes(char* buffer, int size);
TreeNode* generatedMapping(int m[]);
string codingToString(ifstream &in, HuffmanTree &tree);
string turnToString(ifstream &in, unsigned long long int size);
void writeToFileInBinary(ofstream &dest, string &code);
void unCompressed(ifstream &in, ofstream &out, unordered_map<string, int> &c, unsigned long long int size);

#endif //FINALE_TOOLS_HPP
