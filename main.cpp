#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <utility>
#include <deque>
#include <cstring>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <sstream>
#include <cmath>
#include <bitset>
#include <iomanip>
#include <unordered_map>
#include <fstream>

using namespace std;

struct TreeNode{
    string str = "";
    TreeNode *left = nullptr, *right = nullptr;

    bool operator==(const TreeNode& other){
        if(this->str != other.str)
            return false;

        return !((left == nullptr && right != nullptr) || (left != nullptr && right == nullptr) ||
                 (&(left) == &(right)));

    }

};

struct cmp {
    bool operator()(pair<TreeNode*, int> a, pair<TreeNode*, int> b) {
        return a.second > b.second;
    }
};

class HuffmanTree{
private:
    string serializationString = "";
    TreeNode* root = new TreeNode();
    unordered_map<string,string> coding;

    void serialization(string suffix){     //序列化
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()) {
            if (!q.front()) {
                serializationString += (suffix == "txt" ? "@" : "@@@");
            } else {
                string ch = q.front()->str;
                serializationString += (ch == "" ? (suffix == "txt" ? "^" : "^^^") : ch);
                q.push(q.front()->left);
                q.push(q.front()->right);
            }
            q.pop();
        }

    }


    TreeNode* create(string &str, string &suffix){  //反序列化

        vector<TreeNode*> vec = {nullptr};
        for (int i = 0; i < str.size();) {
            char byte = str[i], counter = 0;
            if(suffix == "txt") {
                if (byte < 0) {
                    bitset<8> bits(byte);
                    for (int j = 7; j >= 0; --j) {
                        if (bits[j] == 0)
                            break;
                        counter++;
                    }
                } else
                    counter = 1;
            }else counter = 3;

            string s = "";
            TreeNode *node = new TreeNode;

            char *temp = new char[counter];
            for (int k = 0; k < counter; ++k)
                if(i+k<str.size())
                    temp[k] = str[i + k];
                else
                    temp[k] = 7;
            s += temp;


            if(suffix == "txt") {
                if (s == "@") {
                    vec.push_back(nullptr);
                    i++;
                } else {
                    node->str = s == "^" ? "" : s;
                    vec.push_back(node);
                    i += counter;
                }
            }else{
                if (s == "@@@") {
                    vec.push_back(nullptr);
                    i+=3;
                } else {
                    node->str = s == "^^^" ? "" : s;
                    vec.push_back(node);
                    i += 3;
                }
            }
        }

        int counter = 1;
        for (int l = 1; l < vec.size(); ++l) {
            if(vec[l] == nullptr)
                continue;
            vec[l]->left = counter * 2 < vec.size() ? vec[counter * 2] : nullptr;
            vec[l]->right = counter * 2 + 1 < vec.size() ? vec[counter * 2 + 1] : nullptr;
            counter++;
        }
        return vec[1];
    }

    void encode(unordered_map<string,string> &a, string now, TreeNode* node){   //编码，将<汉字，编码>对，保存到第三方map中
        if(!node)
            return;
        if(node->str != ""){
            a[node->str] = now;
        }
        encode(a, (now + '0'), node->left);
        encode(a, (now + '1'), node->right);

    }

    void decode(unordered_map<string,string> &a, string now, TreeNode* node){   //解码，将<编码，汉字>对，保存在第三方map中
        if(!node)
            return;
        if(node->str != ""){
            a[now] = node->str;
        }
        decode(a, (now + '0'), node->left);
        decode(a, (now + '1'), node->right);
    }

public:
    HuffmanTree(TreeNode* node){
        root = node;
        encode(coding, "", root);
    }

    HuffmanTree(string &str, string path){
        string suffix = path.substr(path.rfind('.')+1);
        root = create(str, suffix);
        encode(coding, "", root);
    }

    void decodeSelf(unordered_map<string,string> &a){
        decode(a, "", root);
    }

    string getSerializationString(string suffix){
        if(serializationString == "")
            serialization(suffix);
        return serializationString;
    }

    unordered_map<string, string> &getCoding() {
        return coding;
    }

};

// __________分界线____________

TreeNode* generatedMapping(unordered_map<string, int> m){   //没问题
    priority_queue<pair<TreeNode*,int>, vector<pair<TreeNode*,int>>, cmp> pq;
    for (auto ite = m.begin(); ite != m.end(); ite++){
        TreeNode *node = new TreeNode();
        node->str = ite->first;
        pq.push({node, ite->second});
    }

    while(pq.size() != 1){
        int sum = 0;
        TreeNode *node1 = pq.top().first;
        sum += pq.top().second;
        pq.pop();
        TreeNode *node2 = pq.top().first;
        sum += pq.top().second;
        pq.pop();

        TreeNode *node3 = new TreeNode();
        node3->left = node1, node3->right = node2;
        pq.push({node3,sum});
    }

    if(pq.top().first->str != ""){
        TreeNode* node = new TreeNode();
        node->left = pq.top().first;
        pq.pop();
        pq.push({node,1});
    }

    return pq.top().first;

}

TreeNode* countTimes(char* buffer, int size, const string& path){   //没问题
    string suffix = path.substr(path.rfind('.')+1);
    unordered_map<string, int> m;

    for (int i = 0; i < size;) {
        char front = buffer[i], counter = 0;
        bitset<8> bits(front);

        if(suffix == "txt") {
            for (int k = 7; k >= 0; --k) {
                if (bits[k] == 0)
                    break;
                counter++;
            }
            counter = counter == 0 ? 1 : counter;
        }else
            counter = 3;

        string str;
        str.clear();
        for (int j = 0; j < counter; ++j) {
            if(i + j < size)
                str += buffer[i+j];
            else
                str += 7;
        }
        m[str]++;
        i += counter;
    }

    return generatedMapping(m);
}

TreeNode* readAllFromFile(ifstream &in, string &path){  //没问题
    in.seekg(0, ios_base::end);
    int size = in.tellg();
    in.seekg(0, ios_base::beg);
    char *buffer = new char[size];
    memset(buffer, 0, sizeof(buffer));
    in.read(buffer, size);
    in.seekg(0, ios_base::beg);
    return countTimes(buffer, size, path);
}

string codingToString(ifstream &in, HuffmanTree &tree, string path){    //这个函数没问题
    unordered_map<string,string> b = tree.getCoding();
    string code = "", suffix = path.substr(path.rfind('.')+1);;
    in.seekg(0, ios_base::end);
    int size = in.tellg();
    in.seekg(0, ios_base::beg);
    char *buffer = new char[size];
    memset(buffer, 0 , sizeof(buffer));
    in.read(buffer, size);
    in.seekg(0, ios_base::beg);

    for (int i = 0; i < size;) {
        char front = buffer[i], counter = 0;
        bitset<8> bits(front);

        if(suffix == "txt") {
            for (int k = 7; k >= 0; --k) {
                if (bits[k] == 0)
                    break;
                counter++;
            }
            counter = counter == 0 ? 1 : counter;
        }else
            counter = 3;

        string str;
        for (int j = 0; j < counter; ++j) {
            if(i + j < size)
                str += buffer[i+j];
            else
                str += 7;
        }
        code += b[str];
        i += counter;
    }
    in.seekg(0, ios_base::beg);
    return code;
}

void writeToFileInBinary(ofstream &dest, string &code){
    for (int l = 0; l < code.size(); l+=8) {
        bitset<8>bits(0);
        for (int i = 0; i < 8; ++i) {
            if(l+i >= code.size())
                break;
            bits[7-i] = (0 ^ (code[l+i] - '0'));
        }
        char temp = bits.to_ulong();
        dest.write(&temp, 1);
    }
}

string turnToString(ifstream &in, int size){
    string binaryData;
    char ch;
    while(in.tellg()*8 < size){
        ch = 0;
        in.read(&ch, 1);
        bitset<8> bits(ch);
        string temp = bits.to_string();
        if(in.tellg()*8 > size)
            temp = temp.substr(0,8-in.tellg()*8+size);
        binaryData.append(temp);
    }
    return binaryData;
}


void unCompressed(ifstream &in, ofstream &out, unordered_map<string,string> &c, int size){
    string binaryData = turnToString(in, size);

    int i = 0, j = 1;
    while(i+j <= size){
        while(i+j <= size && c.find(binaryData.substr(i,j)) == c.end()) {
            j++;
        }
        if(i+j <= size)
            out << c[binaryData.substr(i, j)];
        i += j;
        j = 1;
    }
}

void easyOne(string binaryData, ofstream &out, unordered_map<string,string> &c, int size){
    int i = 0, j = 1;
    while(i+j <= size){
        while(i+j <= size && c.find(binaryData.substr(i,j)) == c.end()) {
            j++;
        }
        if(i+j <= size)
            out << c[binaryData.substr(i, j)];
        i += j;
        j = 1;
    }
}

int main() {

    cout<<"请选择功能，输入 C 以压缩文件，输入 U 以解压文件: ";
    char boo;
    cin>>boo;
    if(boo == 'C') {

        cout << "请输入你想要压缩的文件的绝对路径名: ";
        string str;
        cin >> str;
        ifstream originFile = ifstream(str, ios::binary);
        ofstream compressFile = ofstream("compressedFile.txt", ios::binary);
        ofstream configuration = ofstream("configuration.txt", ios::binary);

        while (!originFile.is_open()) {
            cout << "输入的文件名有误，请重新输入: ";
            cin >> str;
            originFile = ifstream(str, ios::binary);
        }

        HuffmanTree tree(readAllFromFile(originFile, str));
        string code = codingToString(originFile, tree, str);
        string serialString = tree.getSerializationString(str.substr(str.rfind('.')+1));

        writeToFileInBinary(compressFile, code);
        configuration << str << endl << code.size() << endl << serialString.size() << endl;
        char *temp = &(serialString[0]);
        configuration.write(temp,serialString.size());
        cout<<"压缩完成";

        HuffmanTree tree2(serialString, str);

        string ss2 = tree2.getSerializationString(str.substr(str.rfind('.')+1));
        cout<< ss2.size() << endl << serialString.size()<<endl;

        return 0;

    }else if(boo == 'U'){
        ifstream compressFile = ifstream("compressedFile.txt", ios::binary);
        ifstream configuration = ifstream("configuration.txt", ios::binary);
        if(!compressFile.is_open() || !configuration.is_open()){
            cout<<"找不到需要解压的文件，请确认软件根目录下存在 \"compressedFile.txt\" 和\"configuration.txt\"两个文件并确保其文件完整性";
            return 0;
        }

        int size,length;
        string serialString, title, te;
        configuration>>title>>size>>length;
        configuration.get();

        char* temp = new char[length];
        configuration.read(temp,length);
        for (int i = 0; i < length; ++i) {
            serialString += temp[i];
        }

        ofstream unCompressedFile = ofstream(title, ios::binary);
        HuffmanTree tree(serialString,title);
        unordered_map<string,string> mapx;
        tree.decodeSelf(mapx);
        unCompressed(compressFile, unCompressedFile, mapx, size);
        cout<<"解压完毕";

    }

    return 0;
}