
//
//  LinkList.h
//  DataStructure_1
//
//  Created by Leon Wong on 2018/9/17.
//  Copyright © 2018年 Leon. All rights reserved.
//

#ifndef LinkList_h
#define LinkList_h

#include <stdio.h>
#include "LinkNode.h"

class LinkList
{
private:
    LinkNode* first;          //链表头指针
    int cntNode;              //结点计数

public:
    //todo:有参构造函数和复制构造函数
    LinkList(){first = new LinkNode(); cntNode = 0;}    //无参构造函数
    ~LinkList(){makeEmpty(); delete first;}             //析构函数

    void makeEmpty();                                   //将链表置为空表
    LinkNode* getHead() const {return first;}           //获取链表头
    void outputTitle() const;                           //输出表格第一行

    void init();                                        //后插法建立链表
    LinkNode* locate(int location);                     //定位
    void insert();                                      //插入
    void search();                                      //查找
    void modify();                                      //修改
    void deleteData();                                  //删除
    void output() const;                                //统计

};

#endif /* LinkList_h */
