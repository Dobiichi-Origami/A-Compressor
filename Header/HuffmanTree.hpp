//
// Created by TwinTails on 20/12/9.
//

#ifndef FINALE_HUFFMANTREE_HPP
#define FINALE_HUFFMANTREE_HPP

#include "../Header/HuffmanTreeNode.hpp"
#include <unordered_map>

using namespace std;

class HuffmanTree{
private:
    TreeNode* root = new TreeNode();
    unordered_map<int,string> coding;

    void encode(unordered_map<int,string> &a, string now, TreeNode* node);
    void decode(unordered_map<string, int> &a, string now, TreeNode* node);
    void createTree(int m[]);

public:
    HuffmanTree(TreeNode* node);
    HuffmanTree(int weights[]);
    void decodeSelf(unordered_map<string, int> &a);
    unordered_map<int, string> &getCoding();
};

#endif //FINALE_HUFFMANTREE_HPP
