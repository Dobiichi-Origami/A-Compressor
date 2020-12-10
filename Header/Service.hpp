//
// Created by TwinTails on 20/12/9.
//

#ifndef FINALE_SERVICE_HPP
#define FINALE_SERVICE_HPP

#include <iostream>
#include "HuffmanTree.hpp"
#include "HuffmanTreeNode.hpp"
#include "Tools.hpp"

using namespace std;

void encode(){
    cout << "请输入你想要压缩的文件的绝对路径名: ";
    string str;
    getchar();
    getline(cin,str);
    ifstream originFile = ifstream(str, ios::binary);
    ofstream compressFile = ofstream("compressedFile.txt", ios::binary);
    ofstream configuration = ofstream("configuration.txt", ios::binary);

    while (!originFile.is_open()) {
        cout << "输入的文件名有误，请重新输入: ";
        getchar();
        getline(cin,str);
        originFile = ifstream(str, ios::binary);
    }

    HuffmanTree tree(readAllFromFile(originFile));
    string code = codingToString(originFile, tree);
    int *weights = getFrequencyArray(originFile);

    writeToFileInBinary(compressFile, code);
    unsigned long long int size = code.size();
    configuration << str << endl << size << endl;
    configuration.close();

    FILE *configurate = fopen("next.bin", "wb");
    fwrite(weights, sizeof(int), 256, configurate);

    cout<<"压缩完成";
}

void decode(){
    ifstream compressFile = ifstream("compressedFile.txt", ios::binary);
    ifstream configuration = ifstream("configuration.txt", ios::binary);
    FILE *next = fopen("next.bin", "rb");

    if(!compressFile.is_open() || !configuration.is_open() || next == nullptr){
        cout<<"找不到需要解压的文件，请确认软件根目录下存在 \"compressedFile.txt\" ,\"configuration.txt\" 和\"next.bin\"三个文件并确保其文件完整性";
        return ;
    }

    unsigned long long int size;
    string title;
    getline(configuration, title);
    configuration>>size;
    configuration.close();

    ofstream unCompressedFile(title, ios::binary);

    int temp[256];
    memset(temp, 0 , sizeof(temp));
    fread(temp, sizeof(int), 256, next);

    HuffmanTree tree(temp);
    unordered_map<string,int> mapx;
    tree.decodeSelf(mapx);

    unCompressed(compressFile, unCompressedFile, mapx, size);
    cout<<"解压完毕";
}

#endif //FINALE_SERVICE_HPP
