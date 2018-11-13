//
//  main.cpp
//  DataStructure_6
//
//  Created by Leon Wong on 2018/10/29.
//  Copyright © 2018 Leon. All rights reserved.
//

//家族管理系统
//本项目的实质是完成兑家谱成员信息的建立，查找，插入，修改，删除等功能，可以首先定义家族成员数据结构，然后将每个功能作为一个成员函数来完成对数据的操作，最后完成主函数以验证各个函数功能并得到运行结果。


#include <iostream>
#include <string>
#include "Tree.h"

//显示功能菜单
void showMenu()
{
    cout << "**\t\t\t  家族管理系统\t\t\t\t**\n";
    cout << "==========================================\n";
    cout << "**\t\t\t请选择要执行的操作:\t\t\t**\n";
    cout << "**\t\t\tA --- 完善家谱\t\t\t\t**\n";
    cout << "**\t\t\tB --- 添加家族成员\t\t\t**\n";
    cout << "**\t\t\tC --- 解散局部家庭\t\t\t**\n";
    cout << "**\t\t\tD --- 更改家庭成员姓名\t\t\t**\n";
    cout << "**\t\t\tE --- 退出程序\t\t\t\t**\n";
    cout << "==========================================\n";
}

//初始化家族树：添加祖先结点
void init(Tree<string>& f, TreeNode<string>& a)
{
    cout <<"请先建立一个家谱!" << endl;
    cout <<"请输入祖先的姓名:";
    
    cin>>a.data;
    f.setRoot(&a);

    cout << "此家谱的祖先是" << a.data << endl << endl;
}

//执行菜单功能
void execute(Tree<string>& f)
{
    
    char command = 'a';
    while(command != 'E')
    {
        cout << "请选择要执行的操作:" ;
        cin >>command;
        switch(command)
        {
            case 'A':
            {
                cout << "请输入要建立家庭的人的姓名:";
                string name;
                cin >> name;
                if(!f.Find(name))
                    cout << "找不到这个人，请重新输入！" << endl;
                else if(f.getCurrent()->firstChild != nullptr)
                {
                    cout << "他已经有家庭了，请不要破坏！" << endl;
                }
                else
                {
                    //todo
                }
            }
                break;
            case 'B':
            {
                cout << "请输入要添加儿子（或女儿）的人的姓名:";
                string name;
                cin >> name;
                if(!f.Find(name))
                {
                    cout << "找不到这个人，请重新输入！" << endl;
                    break;
                }
                
                cout << "请输入"<< name <<"新的添加儿子（或女儿）的人的姓名:";
                cin >> name;
                //todo
//                insert(thisMan,name);
//                display(thisMan);
            }
                break;
            case 'C':
            {
                cout << "请输入要解散家庭的人的姓名:";
                string name;
                cin >> name;
                if(!f.Find(name))
                {
                    cout << "找不到这个人，请重新输入！" << endl;
                    break;
                }
                cout << "要解散家庭的是" << name << endl;
                //todo
//                display(thisMan);
//                auto child = thisMan->child;
//                thisMan->child = nullptr;
//                deleChild(child);
            }
                break;
            case 'D':
            {
                cout << "请输入要更改姓名的人的目前姓名:";
                string name;
                cin >> name;
                if(!f.Find(name))
                {
                    cout << "找不到这个人，请重新输入！" << endl;
                    break;
                }
                cout << "请输入更改后的姓名:";
                cin >> name;
                //todo
//                changeName(thisMan,name);
                cout << name << endl << endl;
            }
                break;
            case 'E':
                cout <<"\n\n程序已经成功退出！";
                break;
            default :
                cout << "输入错误，请重新输入！" << endl;
                break;
        }
    }
    
    
}


int main(int argc, const char * argv[])
{
    Tree<string> family;
    TreeNode<string> ancestor("temp");
    
    showMenu();
    init(family, ancestor);
    execute(family);
    
    return 0;
}
