#include <iostream>
#include "Header/AllMyClass.hpp"

int main() {

    cout<<"请选择功能，输入 C 以压缩文件，输入 U 以解压文件: ";
    char boo;
    cin>>boo;
    if(boo == 'C') {

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
        return 0;

    }else if(boo == 'U'){
        ifstream compressFile = ifstream("compressedFile.txt", ios::binary);
        ifstream configuration = ifstream("configuration.txt", ios::binary);
        FILE *next = fopen("next.bin", "rb");

        if(!compressFile.is_open() || !configuration.is_open() || next == nullptr){
            cout<<"找不到需要解压的文件，请确认软件根目录下存在 \"compressedFile.txt\" 和\"configuration.txt\"两个文件并确保其文件完整性";
            return 0;
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


    return 0;
}