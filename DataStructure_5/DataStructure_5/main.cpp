//
//  main.cpp
//  DataStructure_5
//
//  Created by Leon Wong on 2018/10/29.
//  Copyright © 2018 Leon. All rights reserved.
//


//项目内容：
//设某银行有A，B两个业务窗口，且处理业务的速度不一样，其中A窗口处理速度是B窗口的2倍----即当A窗口每处理完2个顾客是，B窗口处理完1个顾客。给定到达银行的顾客序列，请按照业务完成的顺序输出顾客序列。假定不考虑顾客信后到达的时间间隔，并且当不同窗口同时处理完2个顾客时，A窗口的顾客优先输出。

//输入说明：输入为一行正整数，其中第一数字N（N<=1000）为顾客总数，后面跟着N位顾客的编号。编号为奇数的顾客需要到A窗口办理业务，为偶数的顾客则去B窗口。数字间以空格分隔。
//输出说明：按照业务处理完成的顺序输出顾客的编号。数字键以空格分隔，但是最后一个编号不能有多余的空格。

//数据结构：链式队列

#include <iostream>
#include "LinkedQueue.h"

/*
 *@brief: 读取所有顾客数据，并按照顺序将奇数编号的顾客存入窗口A的顾客队列，偶数编号的顾客存入窗口B的顾客队列。
 */
void readData(int sum, LinkedQueue<int>& win_1, LinkedQueue<int>& win_2)
{
    int cnt;
    int tempCustomer;
    for (cnt = 0; cnt < sum; cnt++)
    {
        cin >> tempCustomer;
        if (tempCustomer % 2)
            win_1.EnQueue(tempCustomer);
        else
            win_2.EnQueue(tempCustomer);
        
    }
    
}


/*
 *@brief: 通过分析题意简化算法。首先按照三个一组的顺序输出顾客，输出两个窗口A中的顾客，然后输出一个窗口B中的顾客。直至某个窗口的顾客全部处理完，然后直接输出另一个窗口剩余的所有顾客。
 */
void handle(int sum, LinkedQueue<int>& win_1, LinkedQueue<int>& win_2)
{
    int cntCustomers;               //已经处理的顾客计数
    int temp = 0;                   //暂时存放待输出数据
    bool continueHandle = true;      //是否继续按照三个一组的方式进行处理
    for (cntCustomers = 1; cntCustomers <= sum && continueHandle; cntCustomers++)
    {
        switch (cntCustomers % 3) {
            case 1:
            case 2:
                if(!win_1.IsEmpty())
                {
                    win_1.DeQueue(temp);
                    std::cout << temp;
                    
                    if(!win_1.IsEmpty() || !win_2.IsEmpty())
                        std::cout << " ";
                }
                else
                {
                    continueHandle = false;
                }
                break;
                
            case 0:
                if(!win_2.IsEmpty())
                {
                    win_2.DeQueue(temp);
                    std::cout << temp;
                    
                    if(!win_1.IsEmpty() || !win_2.IsEmpty())
                        std::cout << " ";
                }
                else
                {
                    continueHandle = false;
                }
                break;
                
            default:
                break;
        }
    }
    
    while (!win_1.IsEmpty()) {
        win_1.DeQueue(temp);
        std::cout << temp;
        if(!win_1.IsEmpty())
            std::cout << " ";
    }
    
    while (!win_2.IsEmpty()) {
        win_2.DeQueue(temp);
        std::cout << temp;
        if(!win_2.IsEmpty())
            std::cout << " ";
    }
    
}

int main(int argc, const char * argv[])
{
    int SumCustomers;
    LinkedQueue<int> window_1;
    LinkedQueue<int> window_2;
//    LinkedQueue<int>* window_1 = new LinkedQueue<int>();
//    LinkedQueue<int>* window_2 = new LinkedQueue<int>();
    
    std::cin >> SumCustomers;
    
    readData(SumCustomers, window_1, window_2);
    
    handle(SumCustomers, window_1, window_2);
    
    
    
    //std::cout<<window_1<<endl<<window_2;
    

    return 0;
}
