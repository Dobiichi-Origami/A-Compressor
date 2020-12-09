#include <iostream>
#include "Header/AllMyClass.hpp"

using namespace std;

int main() {

    cout<<"请选择功能，输入 C 以压缩文件，输入 U 以解压文件: ";
    char boo;
    cin>>boo;
    if(boo == 'C') {
        encode();
    }else if(boo == 'U'){
        decode();
    }


    return 0;
}