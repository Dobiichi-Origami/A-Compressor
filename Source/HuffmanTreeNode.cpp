#include "../Header/HuffmanTreeNode.hpp"
#include <utility>

using namespace std;

bool TreeNode::operator==(const TreeNode &other) {
    if(this->val != other.val)
        return false;

    return !((left == nullptr && right != nullptr) || (left != nullptr && right == nullptr) ||
             (&(left) == &(right)));
}

bool cmp::operator()(pair<TreeNode *, int> a, pair<TreeNode *, int> b) {
    return a.second > b.second;
}
