
//
//  LinkList.cpp
//  DataStructure_1
//
//  Created by Leon Wong on 2018/9/17.
//  Copyright © 2018年 Leon. All rights reserved.
//

#include <iostream>
#include <string>
#include <iomanip>
#include "LinkList.h"

/*
 @brief 建立考生信息系统，实质是采用后插法建立单链表
*/
void LinkList::init()
{
    LinkNode* newNode, *last = this->first;

    std::cout<<"首先请建立考生信息系统！"<<std::endl<<"请输入考生人数：";
    int cntStudent;
    std::cin>>cntStudent;
    while(cntStudent<=0)
    {
        std::cout<<"至少输入一名考生的信息，请重新输入考生人数：";
        std::cin>>cntStudent;
    }

    std::cout<<"请依次输入考生的考号，姓名，性别，年龄及报考类别！"<<std::endl;

    StudentData tempData;                      //用于暂时存储输入数据
    for(int cnt=1; cnt<=cntStudent; cnt++)
    {
        std::cin>>tempData.id>>tempData.name>>tempData.sex>>tempData.age>>tempData.category;
        newNode = new LinkNode(tempData);
        if(newNode == nullptr)
        {
            std::cerr<<"存储分配错误！"<<std::endl;
            exit(1);
        }
        last->next = newNode;
        last = newNode;
        this->cntNode++;                       //链表结点数+1
    }
}

/*
 @brief 定位函数，返回链表中第location个结点的地址。
 @param 需要定位的结点的序号location
 @return 结点的地址
 */
LinkNode* LinkList::locate(int location)
{
    if (location<0 || location>this->cntNode)
    {
        return nullptr;
    }
    LinkNode* current = first; int k = 0;
    while ( current != nullptr && k < location)
    {
        current = current->next; k++;
    }
    return current;
}

/*
 @brief 插入函数，将新元素newData插入在链表中第location个结点之后，最后输入数据库
 */
void LinkList::insert()
{
    int location;
    StudentData newData;

    std::cout<<"请输入你要插入的考生的位置：";
    std::cin>>location;
    LinkNode* current = locate(location - 1);
    while (current == nullptr)
    {
        std::cout<<"您输入的位置不合法，请重新输入：";
        std::cin>>location;
        current = locate(location - 1);
    }
    std::cout<<"请依次输入要插入的考生的考号，姓名，性别，年龄及报考类别！"<<std::endl;
    std::cin>>newData.id>>newData.name>>newData.sex>>newData.age>>newData.category;
    LinkNode* newNode = new LinkNode(newData);
    if(newNode == nullptr)
    {
        std::cerr<<"存储分配错误！"<<std::endl;
        exit(1);
    }
    newNode->next = current->next;
    current->next = newNode;
    this->cntNode++;                             //链表结点数+1，插入成功
    output();
}

/*
 @brief 查找考号为id的考生数据并输出
 */
void LinkList::search()
{
    string  id;
    std::cout<<"请输入要查找的考生的考号：";
    std::cin>>id;
    LinkNode* current = this->first->next;
    while (current != nullptr)
    {
        if(current->data.id == id)
        {
            outputTitle();
            std::cout<<setiosflags(ios::left);
            std::cout <<setw(7)<<current->data.id <<setw(8)<<current->data.name <<setw(8)<<current->data.sex <<setw(7)<<current->data.age <<setw(7)<<current->data.category << std::endl;
            return;
        }
        else
        {
            current = current->next;
        }
    }
    std::cout<<"您要查找的考生不存在。"<<std::endl;
}

/*
 @brief 修改考号为id的考生数据并输出修改后的数据库
 */
void LinkList::modify()
{
    string  id;
    std::cout<<"请输入要修改的考生的考号：";
    std::cin>>id;
    LinkNode* current = this->first->next;
    while (current != nullptr)
    {
        if(current->data.id == id)
        {
            std::cout<<"请依次输入要修改的考生的考号，姓名，性别，年龄及报考类别！"<<std::endl;
            std::cin >> current->data.id >> current->data.name >> current->data.sex >> current->data.age >> current->data.category;
            output();
            return;
        }
        else
        {
            current = current->next;
        }
    }
    std::cout<<"您要修改的考生不存在。"<<std::endl;
}

/*
 @brief 删除考号为id的考生数据并输出删除后的数据库
 */
void LinkList::deleteData()
{
    string  id;
    std::cout<<"请输入要删除的考生的考号：";
    std::cin>>id;
    LinkNode* current = this->first;
    while (current->next != nullptr)
    {
        if(current->next->data.id == id)
        {
            LinkNode* needDelete = current->next;
            current->next = needDelete->next;
            delete needDelete;
            this->cntNode--;
            output();
            return;
        }
        else
        {
            current = current->next;
        }
    }
    std::cout<<"您要删除的考生不存在。"<<std::endl;
}

/*
 @brief 统计所有考生信息，按顺序输出链表数据
 */
void LinkList::output() const
{
    outputTitle();

    LinkNode* current = first->next;
    while(current != nullptr)
    {
        std::cout<<setiosflags(ios::left);
        std::cout <<setw(7)<<current->data.id <<setw(8)<<current->data.name <<setw(8)<<current->data.sex <<setw(7)<<current->data.age <<setw(7)<<current->data.category << std::endl;
        current = current->next;
    }
}

/*
 @brief 输出表格的第一行
 */
void LinkList::outputTitle() const
{
    std::cout<<setiosflags(ios::left);
    string space = "    ";
    std::cout<<"考号"<<space<<"姓名"<<space<<"性别"<<space<<"年龄"<<space<<"报考类别"<<std::endl;
}

/*
 @brief 将表格置为空表，只留一个表头结点，表头结点在析构函数中释放
 */
void LinkList::makeEmpty()
{
    LinkNode* needDelete;
    while(first->next != nullptr)
    {
        needDelete = first->next;
        first->next = needDelete->next;
        delete needDelete;
        this->cntNode--;
    }
}
