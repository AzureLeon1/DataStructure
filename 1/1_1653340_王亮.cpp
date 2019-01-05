//
//  main.cpp
//  DataStructure_1
//
//  Created by Leon Wong on 2018/9/17.
//  Copyright © 2018年 Leon. All rights reserved.
//


//项目简介：
//考试报名工作给各高校报名工作带来了新的挑战，给教务管理部门增加了很大的工作量。本项目是对考试报名管理的简单模拟，用控制台选项的选择方式完成下列功能：输入考生信息；输出考生信息；查询考生信息；添加考生信息；修改考生信息；删除考生信息。
//
//项目功能要求：
//本项目的实质是完成对考生信息的建立，查找，插入，修改，删除等功能。其中考生信息包括准考证号，姓名，性别，年龄和报考类别等信息。项目在设计时应首先确定系统的数据结构，定义类的成员变量和成员函数；然后实现各成员函数以完成对数据操作的相应功能；最后完成主函数以验证各个成员函数的功能并得到运行结果。（建议采用链表实现）
//


#include <iostream>
#include "LinkNode.h"
#include "LinkList.h"

using namespace std;

int main(int argc, const char * argv[])
{
    LinkList* linkList= new LinkList();

    //建立链表并输出结果
    linkList->init();
    linkList->output();

    //循环处理命令模式
    while(1)
    {
        int command;
        cout<<"请选择您要进行的操作（1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作）："<<endl;
        cin>>command;
        switch (command) {
            case 1:
                linkList->insert();
                break;
            case 2:
                linkList->deleteData();
                break;
            case 3:
                linkList->search();
                break;
            case 4:
                linkList->modify();
                break;
            case 5:
                linkList->output();
                break;
            case 0:
                return 0;

            default:
                cout<<"操作码错误，请重新选择"<<endl;
                break;
        }
    }

    return 0;
}
