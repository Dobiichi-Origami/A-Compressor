#include "../Header/Tools.hpp"
#include <queue>
#include <iostream>

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

    cout<<"正在生成频率矩阵:[ "<<flush;
    int baseline = size/10, sum = 0;

    for (int i = 0; i < size; i++) {
        if(i == sum) {
            cout << '=' << flush;
            sum += baseline;
        }

        int chs = 0;
        chs = buffer[i]+128;
        m[chs]++;
    }

    cout<<"= ] 频率矩阵生成完成"<<endl;

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

    cout<<"正在统计词频:[ "<<flush;
    int baseline = size/10, sum = 0;

    for (int i = 0; i < size; i++) {
        if(i == sum) {
            cout << '=' << flush;
            sum += baseline;
        }

        int chs = 0;
        chs = buffer[i]+128;
        m[chs]++;
    }
    cout<<"= ] 词频统计完成"<<endl;

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

    int size = pq.size(), baseline = size/10, sum = size-baseline;
    cout<<"正在生成哈夫曼树:[ "<<flush;

    while(pq.size() != 1){
        if(size == sum) {
            cout << "=" << flush;
            sum -= baseline;
        }

        size--;
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

    cout<<"= ] 哈夫曼树生成完成"<<endl;

    return pq.top().first;
}

string codingToString(ifstream &in, HuffmanTree &tree) {
    unordered_map<int, string> b = tree.getCoding();
    string code = "";
    int size = getSize(in);
    char *buffer = read(in);

    cout<<"正在将源文件编码为哈夫曼码:[ "<<flush;
    int baseline = size/10, sum = 0;

    for (int i = 0; i < size; ++i) {
        if(i == sum) {
            cout << '=' << flush;
            sum += baseline;
        }
        code += b[buffer[i] + 128];
    }

    cout<<"= ] 文件编码完成"<<endl;
    return code;

}

string turnToString(ifstream &in, unsigned long long int size) {
    string binaryData;
    char ch;
    unsigned long long int const x = 8;
    cout<<"正在读取压缩文件内容:[ "<<flush;
    unsigned long long int baseline = size/10, sum = 0;

    while(in.tellg()*x < size){

        if((in.tellg())*x >= sum) {
            cout << "=" << flush;
            sum += baseline;
        }

        ch = 0;
        in.read(&ch, 1);
        bitset<x> bits(ch);
        string temp = bits.to_string();
        if(in.tellg()*x > size)
            temp = temp.substr(0,x-in.tellg()*x+size);
        binaryData.append(temp);
    }
    cout<<"= ] 文件读取完成"<<endl;
    return binaryData;
}

void writeToFileInBinary(ofstream &dest, string &code) {
    unsigned long long int baseline = code.size()/10, sum = 0;
    cout<<"正在将哈夫曼编码写入文件中:[ "<<flush;

    for (unsigned long long int l = 0; l < code.size(); l+=8) {
        bitset<8>bits(0);
        if(l >= sum) {
            cout << "=" << flush;
            sum += baseline;
        }

        for (unsigned long long int i = 0; i < 8; ++i) {
            if(l+i >= code.size())
                break;
            bits[7-i] = (0 ^ (code[l+i] - '0'));
        }
        char temp = bits.to_ulong();
        dest.write(&temp, 1);
    }
    cout<<"= ] 文件写入完成"<<endl;
}

void unCompressed(ifstream &in, ofstream &out, unordered_map<string, int> &c, unsigned long long int size) {
    string binaryData = turnToString(in, size);

    cout<<"正在解压哈夫曼编码:[ "<<flush;
    unsigned long long int baseline = size/10, sum = 0;

    unsigned long long int i = 0, j = 1;
    while(i+j <= size){
        while(i+j <= size && c.find(binaryData.substr(i,j)) == c.end()) {
            j++;
            if((i+j) >= sum) {
                cout << "=" << flush;
                sum += baseline;
            }
        }
        if(i+j <= size)
            out << (char)(c[binaryData.substr(i, j)]-128);
        i += j;
        j = 1;
    }

    cout<<"= ] 文件解压完成"<<endl;
}

