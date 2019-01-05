//
//  main.cpp
//  DataStructure_3
//
//  Created by Leon Wong on 2018/10/15.
//  Copyright © 2018 Leon. All rights reserved.
//


/*
题目三  勇闯迷宫游戏

项目简介：
迷宫只有两个门，一个门叫入口，另一个门叫出口。一个骑士骑马从入口进入迷宫，迷宫设置很多障碍，骑士需要在迷宫中寻找通路以到达出口。

项目功能要求：
迷宫问题的求解过程可以采用回溯法即在一定的约束条件下试探地搜索前进，若前进中受阻，则及时回头纠正错误另择通路继续搜索的方法。从入口出发，按某一方向向前探索，若能走通，即某处可达，则到达新点，否则探索下一个方向；若所有的方向均没有通路，则沿原路返回前一点，换下一个方向再继续试探，直到所有可能的道路都探索到，或找到一条通路，或无路可走又返回入口点。在求解过程中，为了保证在达到某一个点后不能向前继续行走时，能正确返回前一个以便从下一个方向向前试探，则需要在试探过程中保存所能够达到的每个点的下标以及该点前进的方向，当找到出口时试探过程就结束了。
*/

//解题思路：使用一个栈来存储试探过程中走过的路径，从而将递归算法改为非递归算法
#include <iostream>
#include <iomanip>
#include "SeqStack.h"

//前进方向表
struct offsets
{
    int a, b;
    char* dir;
};

//栈中的三元组结构
struct items
{
    int x, y, dir;    //dir为前进方向表中的下标
};


const int row = 5, col = 5;
offsets direction[4] = { {-1, 0, "up"}, {0, 1, "right"}, {1, 0, "down"}, {0, -1, "left"}};
int maze[row+2][col+2] =
{
    1, 1, 1, 1, 1, 1, 1,
    1, 0, 1, 0, 0, 0, 1,
    1, 0, 1, 0, 1, 1, 1,
    1, 0, 0, 0, 1, 0, 1,
    1, 0, 1, 0, 0, 0, 1,
    1, 0, 1, 0, 1, 0, 1,
    1, 1, 1, 1, 1, 1, 1
};
int mark[row+2][col+2];


/*
 *@brief: 打印迷宫地图
 */
void printMaze()
{
    int cnt1, cnt2;
    cout<<setiosflags(ios::left);
    //输出第一行
    cout<<setw(7)<<"";
    for (cnt1=0; cnt1<=col+1; cnt1++)
    {
        cout<<setw(7)<<to_string(cnt1)+"列";
    }
    cout<<endl;
    //输出迷宫各行
    for (cnt1=0; cnt1<=row+1; cnt1++)
    {
        cout<<setw(8)<<to_string(cnt1)+"行";
        for (cnt2=0; cnt2<=col+1; cnt2++)
        {
            switch (maze[cnt1][cnt2]) {
                case 1:
                    cout<<setw(7)<<"#";
                    break;
                case 0:
                    cout<<setw(7)<<"0";
                    break;
                case 2:
                    cout<<setw(7)<<"x";
                    break;
                default:
                    break;
            }
        }
        cout<<endl;
    }
}

/*
 @brief: 打印路径，不包含出口结点
 */
void printSt(SeqStack<items>& s)
{
    items tempResult;        //用于暂存每个结果
    int cnt;
    for (cnt = 0; cnt <= s.getSize()-1; cnt++)
    {
        if(s.getElementByIndex(cnt, tempResult))
        {
            cout<<"("<<tempResult.x<<", "<<tempResult.y<<") ---> ";
        }
    }
}

/*
 @brief: 使用栈进行回溯从而求解迷宫问题的算法
 */
void seekPath(int targetX, int targetY)
{
    int i, j, d, g, h;
    mark[1][1] = 1;
    SeqStack<items> st;
    items tmp;
    tmp.x = 1; tmp.y = 1; tmp.dir = 1;          //首结点（起点）的第一个搜索方向，（不必向上方搜索）
    st.Push(tmp);
    maze[tmp.x][tmp.y] = 2;
    while (st.IsEmpty() == false)
    {
        st.Pop(tmp);
        maze[tmp.x][tmp.y] = 0;
        i = tmp.x; j = tmp.y; d = tmp.dir;
        while (d < 4)
        {
            g = i+direction[d].a;
            h = j+direction[d].b;
            if (g == targetX && h == targetY)              //到达出口
            {
                tmp.x = i; tmp.y = j; tmp.dir = d;
                st.Push(tmp);
                maze[tmp.x][tmp.y] = 2;
                maze[targetX][targetY] = 2;
                cout<<"迷宫地图："<<endl;
                printMaze();
                cout<<"迷宫路径："<<endl;
                printSt(st);
                cout<<"("<<targetX<<", "<<targetY<<")"<<endl;
                return;
            }
            if (maze[g][h] == 0 && mark[g][h] == 0)
            {
                mark[g][h] = 1;
                tmp.x = i; tmp.y = j; tmp.dir = d;
                st.Push(tmp);
                maze[tmp.x][tmp.y] = 2;
                i = g; j = h; d = 0;
            }
            else d++;
        }
    }
    cout<<"No path in maze."<<endl;
}

int main(int argc, const char * argv[])
{
    int i, j;

    for(i = 0; i < row + 2;  i++)
    {
        for(j = 0; j < col; j++)
        {
            mark[i][j] = 0;
        }
    }

    mark[1][1] = 1;

    seekPath(row, col);

    return 0;
}
