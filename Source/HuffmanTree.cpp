//
// Created by TwinTails on 20/12/9.
//

#include "../Header/HuffmanTree.hpp"
#include <string>
#include <queue>

using namespace std;

void HuffmanTree::encode(unordered_map<int, string> &a, string now, TreeNode *node) {
    if(!node)
        return;
    if(node->val != -1){
        a[node->val] = now;
    }
    encode(a, (now + '0'), node->left);
    encode(a, (now + '1'), node->right);
}

void HuffmanTree::decode(unordered_map<string, int> &a, string now, TreeNode *node) {
    if(!node)
        return;
    if(node->val != -1){
        a[now] = node->val;
    }
    decode(a, (now + '0'), node->left);
    decode(a, (now + '1'), node->right);
}

void HuffmanTree::createTree(int *m) {
    priority_queue<pair<TreeNode*,int>, vector<pair<TreeNode*,int>>, cmp> pq;
    for (int i = 0; i < 256; ++i) {
        if(m[i] == 0)
            continue;
        TreeNode *node = new TreeNode;
        node->val = i;
        pq.push({node, m[i]});
    }

    while(pq.size() != 1){
        int sum = 0;
        TreeNode* node1 = pq.top().first;
        sum += pq.top().second;
        pq.pop();
        TreeNode *node2 = pq.top().first;
        sum += pq.top().second;
        pq.pop();

        TreeNode *node3 = new TreeNode;
        node3->left = node1;
        node3->right = node2;
        pq.push({node3, sum});
    }

    root = pq.top().first;
}

HuffmanTree::HuffmanTree(TreeNode *node) {
    root = node;
    encode(coding, "", root);
}

HuffmanTree::HuffmanTree(int *weights) {
    createTree(weights);
    encode(coding, "", root);
}

void HuffmanTree::decodeSelf(unordered_map<string, int> &a) {
    decode(a, "", root);
}

unordered_map<int, string> &HuffmanTree::getCoding() {
    return coding;
}
