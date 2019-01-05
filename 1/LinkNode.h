
//
//  Student.hpp
//  DataStructure_1
//
//  Created by Leon Wong on 2018/9/17.
//  Copyright © 2018年 Leon. All rights reserved.
//

#ifndef LinkNode_h
#define LinkNode_h

#include <stdio.h>
#include <string>

using namespace std;

class LinkList;           //LinkList类的前视声明

struct StudentData{
    string id;
    string name;
    string sex;
    int age;
    string category;
};

class LinkNode
{
friend class LinkList;    //声明LinkList类为友元类

private:
    StudentData data;     //数据元素域
    LinkNode* next;       //链指针域

public:
    LinkNode()
    {
        this->data.id = "";
        this->data.name = "";
        this->data.sex = "";
        this->data.age = 0;
        this->data.category = "";
        this->next = nullptr;
    }

    LinkNode(const StudentData& input, LinkNode* ptr = nullptr)
    {
        this->data = input;
        this->next = ptr;
    }

};

#endif /* LinkNode_h */
