//
//  main.cpp
//  DataStructure_8
//
//  Created by Leon Wang on 2018/12/10.
//  Copyright © 2018 Leon. All rights reserved.
//


//项目简介
//假设一个城市有n个小区，要实现n个小区之间的电网都能够相互接通，构造这个城市n个小区之间的电网，使总工程造价最低。请设计一个能够满足要求的造价方案。
//
//项目功能要求：
//在每个小区之间都可以设置一条电网线路，都要付出相应的经济代价。n个小区之间最多可以有n（n-1）/2条线路，选择其中的n-1条使总的耗费最少。




//数据结构：图 邻接表（链表）表示 求最小生成树
//done: 选B时的输入不合法检测

#include <iostream>
#include <string>
#include "Graphlnk.h"


#define MAX_SIZE 50

using namespace std;

void showMenu()
{
    cout << "**\t\t\t  电网造价模拟系统\t\t\t\t**\n";
    cout << "==========================================\n";
    cout << "**\t\t\tA --- 创建电网顶点\t\t\t\t**\n";
    cout << "**\t\t\tB --- 添加电网的边\t\t\t\t**\n";
    cout << "**\t\t\tC --- 构造最小生成树\t\t\t**\n";
    cout << "**\t\t\tD --- 显示最小生成树\t\t\t**\n";
    cout << "**\t\t\tE --- 退出程序\t\t\t\t**\n";
    cout << "==========================================\n";
}

void output(Graphlnk<string, int>* grid, MinSpanTree<string, int>* minTree)
{
    int n = minTree->getNum();
    auto edgevalue = minTree->getEdgeValue();
    for(int i=1; i<=n; i++){
        //        cout<<"Edge "<<i<<" : "<<"head = "<<edgevalue[i-1].head<<" ; tail = "<<edgevalue[i-1].tail<<" ; key = "<<edgevalue[i-1].key<<endl;
        cout << grid->getValue(edgevalue[i-1].tail) << "-(" << edgevalue[i-1].key << ")->"<< grid->getValue(edgevalue[i-1].head) << "\t";
    }
    cout << endl;
}

void execute(Graphlnk<string, int>* grid, MinSpanTree<string, int>* minTree)
{
    bool isSystemBuilt = false;   //电网图是否已经建立
    char command = 'a';
    while(command != 'E')
    {
        cout << "请选择操作：";
        cin >> command;
        switch (command) {
            case 'A':
                if (isSystemBuilt)
                {
                    cout << "电网定点已经被创建，请重新选择！" <<endl;
                    break;
                }
                else
                {
                    int cnt;
                    int numVertices;
                    string tempName = "";
                    
                    cout << "请输入顶点的个数：";
                    cin >> numVertices;
                    cout << "请依次输入各顶点的名称：" <<endl;
                    for (cnt = 0; cnt < numVertices; cnt++)
                    {
                        cin >> tempName;
                        //cout << tempName <<endl;
                        grid->insertVertex(tempName);
                    }
                    isSystemBuilt = true;
                }
                cout << endl;
                break;
                
            case 'B':
                if (!isSystemBuilt)
                {
                    cout << "请先创建电网顶点！" <<endl;
                    break;
                }
                else
                {
                    string v1 = "init", v2 = "init";
                    int edge = -1;
                    bool isSuccessful = true;                     //是否成功插入边，添加电网的边时使用，当顶点不存在或边已经被插入过时为false
                    
                    while (true)
                    {
                        if (isSuccessful == true)
                        {
                            cout << "请输入两个顶点及边：";
                        }
                        isSuccessful = true;                      //重新置为true
                        cin >> v1 >> v2 >> edge;
                        if (v1=="?" && v2=="?" && edge==0)
                            break;
                        
                        //输入合法检测
                        int i_v1 = grid->getVertexPos(v1);
                        int i_v2 = grid->getVertexPos(v2);
                        if (i_v1 == -1 || i_v2 == -1)
                        {
                            cout << "顶点不存在，请重新输入两个顶点及边：";
                            isSuccessful = false;
                        }
                        else
                        {
                            isSuccessful = grid->insertEdge(i_v1, i_v2, edge);
                            if (!isSuccessful)
                            {
                                cout << "边已存在，请勿重复输入。请重新输入两个顶点及边：";
                            }
                        }
                        
                    }
                    
                }
                cout << endl;
                break;
            case 'C':
                if(!isSystemBuilt)
                {
                    cout << "请先创建电网顶点！" <<endl;
                    break;
                }
                else
                {
                    string tempName;
                    cout << "请输入起始顶点：";
                    cin >> tempName;
                    grid->Prim(*minTree, grid->getVertexPos(tempName));
                    cout << "生成Prim最小生成树！" << endl;
                }
                cout << endl;
                break;
                
            case 'D':
                if(!isSystemBuilt)
                {
                    cout << "请先创建电网顶点！" <<endl;
                    break;
                }
                else
                {
                    cout << "最小生成树的顶点及边为：" << endl;
                    output(grid, minTree);
                }
                cout << endl;
                break;
                
            case 'E':
                cout << endl << endl << "程序已经成功退出！" << endl;
                break;
                
            default:
                cout << "输入错误，请重新输入！" << endl;
                break;
        }
    }
}

int main(int argc, const char * argv[]) {
    Graphlnk<string, int>* powerGrid = new Graphlnk<string, int>(MAX_SIZE);
    MinSpanTree<string, int>* minSpanTree = new MinSpanTree<string, int>();

    showMenu();
    execute(powerGrid, minSpanTree);
    
    
    delete powerGrid;
    delete minSpanTree;
    
    return 0;
}
