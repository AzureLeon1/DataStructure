//
//  main.cpp
//  DataStructure_9
//
//  Created by Leon Wang on 2018/12/14.
//  Copyright © 2018 Leon. All rights reserved.
//



//数据结构：图（AOE网络）
//问题：求关键活动； 为了便于按照要求输出结果，结果用二维数组存储

//有向图插入一条边时，邻接表中之插入一个边结点，不插入两个，所以修改了Graphlnk中的insertVertex()
//题目数据特点：定边编号从1开始，不是从0开始。

#include <iostream>
#include "Graphlnk.h"

using namespace std;

struct edgeWithOrder
{
    int startVertex;
    int endVertex;
    int orderOfInput;
};

/*
 *@brief: 初始化图。读入顶点个数和边的个数，创建顶点。
 *        暂时令各顶点的编号等于 其在NodeTable中的位置+1；位置为0,1,2,3,...,n-1； 编号为1,2,3,...,n
 */
template <typename T, typename E>
void initGraph(Graphlnk<T, E>* gl, int& v, int& e)
{
    cin >> v >> e;
    for (int cnt = 1; cnt <= v; cnt++)
    {
        gl->insertVertex(cnt);
    }
    
}

/*
 *@brief: 插入各条带权边，然后进行拓扑排序，并把排序结果存在order数组中。
 */
template <typename T, typename E>
bool topologicalSort(Graphlnk<T, E>* gl, int numV, int numE, int* order)
{
    int start, end, weight, w, v, cnt;
    int top = -1;
    int n = numV;
    int* count = new int[n];
    for (cnt = 0; cnt < n; cnt++) count[cnt] = 0;
    for (cnt = 0; cnt < numE; cnt++)
    {
        cin >> start >> end >> weight;
        gl->insertEdge(gl->getVertexPos(start), gl->getVertexPos(end), weight);
        count[gl->getVertexPos(end)]++;
    }
    
//
//    for (int i=0; i < numV; i++)
//        cout << count[i] << " ";
//    cout << endl;
    
    
    
    for (cnt = 0; cnt < numV; cnt++)            
    {
        if (count[cnt] == 0)
        {
            count[cnt] = top;
            top = cnt;
        }
    }
    
//    for (int i=0; i < numV; i++)
//        cout << count[i] << " ";
//    cout << endl;
    
    
    for (cnt = 0; cnt < numV; cnt++)
    {
        if ( top == -1 )
        {
            return false;
        }
        else
        {
            v = top; top = count[top];
            order[cnt] = v;
            //cout << cnt << " " << order[cnt] << endl;
            w = gl->getFirstNeighbor(v);
            while(w != -1)
            {
                if (--count[w] == 0)
                {
                    count[w] = top;
                    top = w;
                }
                w = gl->getNextNeighbor(v, w);
            }
        }
    }
    return true;
}

/*
 *@brief: 求关键活动，结果保存在二维数组resultMtx中
 */
template <typename T, typename E>
void keyActivities(Graphlnk<T, E>* gl, int numV, int* order, int** rMtx)
{
    int i, j, k;
    E Ae, Al, w;
    E* Ve = new E[numV];
    E* Vl = new E[numV];
    for(i = 0; i < numV; i++)Ve[i] = 0;
    for(i = 0; i < numV; i++)
    {
        j = gl->getFirstNeighbor(order[i]-1);
        while(j!=-1)
        {
            w = gl->getWeight(order[i]-1, j);
            if(Ve[order[i]-1] + w > Ve[j]) Ve[j] = Ve[order[i]-1] + w;
            j = gl->getNextNeighbor(order[i]-1, j);
        }
    }
    
    cout << Ve[order[numV-1]] << endl;         //输出完成整个项目所需要的时间
    
//    for (int x = 0; x < numV; x++)
//        cout << Ve[x] << " ";
//    cout << endl;
    
    for(int x = 0; x < numV; x++)
        Vl[order[x]] = Ve[order[numV-1]];
    for(j = numV-2; j > 0; j--)
    {
        k = gl->getFirstNeighbor(order[j]);
        while(k!=-1)
        {
            w = gl->getWeight(order[j], k);
            if(Vl[k] - w < Vl[order[j]]) Vl[order[j]] = Vl[k] - w;
            k = gl->getNextNeighbor(order[j], k);
        }
    }
    
//    for (int x = 0; x < numV; x++)
//        cout << Vl[x] << " ";
//    cout << endl;

    
    for(i = 0; i < numV; i++)
    {
        j = gl->getFirstNeighbor(i);
        while(j != -1)
        {
            Ae = Ve[i]; Al = Vl[j] - gl->getWeight(i, j);
            if (Al == Ae)
                rMtx[i][j] = 1;
            j = gl->getNextNeighbor(i, j);
        }
    }
    delete[] Ve; delete[] Vl;
}


/*
 *@brief: 按照要求输出
 */
template <typename T, typename E>
void output(Graphlnk<T, E>* gl, int** rMtx, int numV)
{
    int tempVertex;
    int i;
    for(i = 0; i < numV; i++)
    {
        tempVertex = gl->getFirstNeighbor(i);      //结合插入边时的边链表链入结点的方式，每个节点直接从前向后遍历边链表即可。
        while (tempVertex != -1)
        {
            if (rMtx[i][tempVertex] == 1)
            {
                cout << gl->getValue(i) << "->" << gl->getValue(tempVertex) << endl;
            }
            tempVertex = gl->getNextNeighbor(i, tempVertex);
        }  
    }
}

int main(int argc, const char * argv[])
{
    int numVertex, numEdge;
    Graphlnk<int, int>* graph = new Graphlnk<int, int>();
    
    initGraph(graph, numVertex, numEdge);
    
    int order[numVertex];                      //节点的拓扑顺序，值为order[n]的节点的拓扑顺序是n
    
    int** resultMtx = new int*[numVertex];     //二维数组存储结果，为了实现要求的输出顺序
    for (int i = 0; i < numVertex; i++)
    {
        resultMtx[i] = new int[numVertex];
    }
    for (int i = 0; i < numVertex; i++)
        for (int j = 0; j < numVertex; j++)
            resultMtx[i][j] = 0;
    
    bool isFeasible = topologicalSort(graph, numVertex, numEdge, order);
    
//    for(int i = 0; i < numVertex; i++)
//        cout << order[i] << endl;
    
    if (!isFeasible)
    {
        cout << 0 << endl;
        return 0;
    }
    
    keyActivities(graph, numVertex, order, resultMtx);
    
    output(graph, resultMtx, numVertex);
    
    delete graph;
    for (int i = 0; i < numVertex; i++)
        delete[] resultMtx[i];
    delete[] resultMtx;
    
    return 0;
}
