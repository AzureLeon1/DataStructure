//
//  main.cpp
//  DataStructure_2
//
//  Created by Leon Wong on 2018/9/26.
//  Copyright © 2018 Leon. All rights reserved.
//

//项目内容
//已知两个非降序链表序列S1和S2，设计函数构造出S1和S2的交集新链表S3。
//
//项目功能要求：(要求采用链表)
//1.输入说明：输入分2行，分别在每行给出由若干个正整数构成的非降序序列，用-1表示序列的结尾（-1不属于这个序列）。数字用空格间隔。
//2.输出说明：在一行中输出两个输入序列的交集序列，数字间用空格分开，结尾不能有多余空格；若新链表为空，输出NULL。


//todo:内存释放

#include <iostream>

class LinkList;

class LinkNode
{
    friend class LinkList;    //声明LinkList类为友元类
    
private:
    int data;                 //数据元素域
    LinkNode* next;           //链指针域
    
public:
    LinkNode()
    {
        this->data = 0;
        this->next = nullptr;
    }
    
    LinkNode(const int& input, LinkNode* ptr = nullptr)
    {
        this->data = input;
        this->next = ptr;
    }
    
    LinkNode* getNext() const
    {
        return next;
    }
    
    int getData() const
    {
        return data;
    }
    
};

class LinkList
{
private:
    LinkNode* first;          //链表头指针
    LinkNode* last;           //链表尾指针
    int cntNode;              //结点计数
    
public:
    LinkList(){first = new LinkNode(); last = first; cntNode = 0;}    //无参构造函数
    ~LinkList(){makeEmpty(); delete first;}                           //析构函数
    
    void makeEmpty();                                                 //将链表置为空表
    LinkNode* getHead() const {return first;}                         //获取链表头
    
    void init();                                                      //后插法建立链表
    void insertToTail(int newData);                                              //向链表尾部插入数据
    void output() const;                                              //输出
    
};

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

void LinkList::init()
{
    int temp;
    std::cin>>temp;
    while(temp != -1)
    {
        insertToTail(temp);
        std::cin>>temp;
    }
}

void LinkList::insertToTail(int newData)
{
    LinkNode* newNode = new LinkNode(newData);
    if(newNode == nullptr)
    {
        std::cerr<<"存储分配错误！"<<std::endl;
        exit(1);
    }
    last->next = newNode;
    last = newNode;
    cntNode++;
}

void LinkList::output() const
{
    if(cntNode == 0)
    {
        std::cout<<"NULL"<<std::endl;
    }
    else
    {
        LinkNode* current = first->next;
        while(current != nullptr)
        {
            std::cout << current->data;
            if(current->next != nullptr)
            {
                std::cout<<" ";
            }
            else
            {
                std::cout<<std::endl;
            }
            current = current->next;
        }
    }
}

/*
 @brief:求两个链表的非降序链表的交集，并保存在链表result中
 */
void intersection(LinkList* input1, LinkList* input2, LinkList* result)
{
    LinkNode* p1 = input1->getHead()->getNext();
    LinkNode* p2 = input2->getHead()->getNext();
    
    while(p1!=nullptr && p2!=nullptr)
    {
        if(p1->getData() == p2->getData())
        {
            result->insertToTail(p1->getData());
            p1 = p1->getNext();
            p2 = p2->getNext();
        }
        else if(p1->getData() > p2->getData())
        {
            p2 = p2->getNext();
        }
        else
        {
            p1 = p1->getNext();
        }
    }
    
}

int main(int argc, const char * argv[])
{
    LinkList* s1= new LinkList();
    LinkList* s2= new LinkList();
    LinkList* s3= new LinkList();
    
    std::cout<<"请输入两个非降序链表序列（用-1表示结尾）："<<std::endl;
    s1->init();
    s2->init();
    
    intersection(s1, s2, s3);
    
    s3->output();
    
    return 0;
}
