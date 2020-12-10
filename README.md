# 项目简介

本项目是一个实验性质的简要Demo，目前仅仅在最低层次上实现了最基础的功能，后续更新待定

# 项目结构简要分析

## Header

###***HuffmanTreeNode.hpp***

该文件内封装了构造哈夫曼树的节点结构体定义，以及用于传入堆排序的比较方式的定义

### ***HuffmanTree.hpp***

哈夫曼树的属性和对应成员函数的定义存放于此，定义了对哈夫曼树编、解码生成字典的方法

### ***Tools.hpp***

定义了一打用于读写文件，实现哈夫曼编码和二进制文件的互相转换，储存和构造哈夫曼树的方法

### ***Service.hpp***

封装了业务流程，提供了对外的encode()和decode()方法

### ***AllMyClass.hpp***

工具性头文件，将上述几个头文件封装在一个头文件中，简化include代码

## Source

### ***HuffmanTreeNode.cpp***

哈夫曼树节点的实现

### ***HuffmanTree.cpp***

哈夫曼树本体的实现

### ***Tools.cpp***

工具类的实现

d

a