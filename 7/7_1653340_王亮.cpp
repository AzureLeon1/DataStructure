//
//  main.cpp
//  DataStructure_7
//
//  Created by Leon Wang on 2018/11/26.
//  Copyright © 2018 Leon. All rights reserved.
//


//项目简介：
//农夫要修理牧场的一段栅栏，他测量了栅栏，发现需要N块木头，每块木头长度为整数Li个长度单位，于是他购买了一个很长的，能锯成N块的木头，即该木头的长度是Li的总和。
//但是农夫自己没有锯子，请人锯木的酬金跟这段木头的长度成正比。为简单起见，不妨就设酬金等于所锯木头的长度。例如，要将长度为20的木头锯成长度为8，7和5的三段，第一次锯木头将木头锯成12和8，花费20；第二次锯木头将长度为12的木头锯成7和5花费12，总花费32元。如果第一次将木头锯成15和5，则第二次将木头锯成7和8，那么总的花费是35（大于32）.


//数据结果：哈夫曼树（生成哈夫曼树中使用最小堆 计算WPL使用了栈)


#include <iostream>
#include "HuffmanTree.h"

using namespace std;

int main(int argc, const char * argv[])
{
    int sumBlocks, cnt;
    cin >> sumBlocks;

    while(sumBlocks<=0)
    {
        cout << "木块数量是一个正整数，请重新输入：";
        cin >> sumBlocks;
    }


    int pBlocks[sumBlocks];
    for(cnt = 0; cnt < sumBlocks; cnt++)
    {
        cin >> pBlocks[cnt];
    }

    if (sumBlocks == 1)
    {
        cout << "0" << endl;
        return 0;
    }

    HuffmanTree<int>* blocksTree = new HuffmanTree<int>(pBlocks, sumBlocks);
    //blocksTree->output(blocksTree->getRoot(),"",cout);  cout<<endl;
    cout << blocksTree->getWPL() << endl;


    delete blocksTree;

    return 0;
}
