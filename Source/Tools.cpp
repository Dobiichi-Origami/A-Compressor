#include "../Header/Tools.hpp"
#include <queue>

using namespace std;

char *read(ifstream &in) {
    int size = getSize(in);
    char *buffer = new char[size];
    memset(buffer, 0, sizeof(buffer));
    in.read(buffer, size);
    in.seekg(0, ios_base::beg);
    return buffer;
}

int getSize(ifstream &in) {
    in.seekg(0, ios_base::end);
    int size = in.tellg();
    in.seekg(0, ios_base::beg);
    return size;
}

int *getFrequencyArray(ifstream &in) {
    char *buffer = read(in);
    int size = getSize(in);
    int *m = new int[256];
    memset(m, 0, sizeof(int)*256);

    for (int i = 0; i < size; i++) {
        int chs = 0;
        chs = buffer[i]+128;
        m[chs]++;
    }

    return m;
}

TreeNode *readAllFromFile(ifstream &in) {
    char *buffer = read(in);
    int size = getSize(in);
    return countTimes(buffer, size);
}

TreeNode *countTimes(char *buffer, int size) {
    int m[256];
    memset(m, 0, sizeof(m));

    for (int i = 0; i < size; i++) {
        int chs = 0;
        chs = buffer[i]+128;
        m[chs]++;
    }
    return generatedMapping(m);
}

TreeNode *generatedMapping(int *m) {
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

    return pq.top().first;
}

string codingToString(ifstream &in, HuffmanTree &tree) {
    unordered_map<int, string> b = tree.getCoding();
    string code = "";
    int size = getSize(in);
    char *buffer = read(in);

    for (int i = 0; i < size; ++i)
        code += b[buffer[i]+128];

    return code;

}

string turnToString(ifstream &in, unsigned long long int size) {
    string binaryData;
    char ch;
    unsigned long long int const x = 8;
    while(in.tellg()*x < size){
        ch = 0;
        in.read(&ch, 1);
        bitset<x> bits(ch);
        string temp = bits.to_string();
        if(in.tellg()*x > size)
            temp = temp.substr(0,x-in.tellg()*x+size);
        binaryData.append(temp);
    }
    return binaryData;
}

void writeToFileInBinary(ofstream &dest, string &code) {
    for (unsigned long long int l = 0; l < code.size(); l+=8) {
        bitset<8>bits(0);
        for (unsigned long long int i = 0; i < 8; ++i) {
            if(l+i >= code.size())
                break;
            bits[7-i] = (0 ^ (code[l+i] - '0'));
        }
        char temp = bits.to_ulong();
        dest.write(&temp, 1);
    }
}

void unCompressed(ifstream &in, ofstream &out, unordered_map<string, int> &c, unsigned long long int size) {
    string binaryData = turnToString(in, size);

    unsigned long long int i = 0, j = 1;
    while(i+j <= size){
        while(i+j <= size && c.find(binaryData.substr(i,j)) == c.end()) {
            j++;
        }
        if(i+j <= size)
            out << (char)(c[binaryData.substr(i, j)]-128);
        i += j;
        j = 1;
    }
}

