//
//  main.cpp
//  DataStructure_8
//
//  Created by Leon Wang on 2018/12/10.
//  Copyright © 2018 Leon. All rights reserved.
//



//数据结构：图 邻接表（链表）表示 求最小生成树

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
                    
                    while (true)
                    {
                        cout << "请输入两个顶点及边：";
                        cin >> v1 >> v2 >> edge;
                        cout << endl;
                        if (v1=="?" && v2=="?" && edge==0)
                            break;
                        grid->insertEdge(grid->getVertexPos(v1), grid->getVertexPos(v2), edge);
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
                    cout << endl << "生成Prim最小生成树！" << endl;
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
                    minTree->output();
                }
                cout << endl;
                break;
                
            default:
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
