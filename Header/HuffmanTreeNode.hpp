//
// Created by TwinTails on 20/12/9.
//

#ifndef FINALE_HUFFMANTREENODE_HPP
#define FINALE_HUFFMANTREENODE_HPP

#include <utility>

using namespace std;

struct TreeNode{
    int val = -1;
    TreeNode *left = nullptr, *right = nullptr;
    bool operator==(const TreeNode& other);
};

struct cmp{
    bool operator()(pair<TreeNode*, int> a, pair<TreeNode*, int> b);
};

#endif //FINALE_HUFFMANTREENODE_HPP
