//
//  main.cpp
//  DataStructure_4
//
//  Created by Leon Wong on 2018/10/16.
//  Copyright © 2018 Leon. All rights reserved.
//


//将中缀表达式转换成为后缀表达式

//题目文档中减号格式有问题

//todo: 输出结尾不应有空格

#include <iostream>
#include "SeqStack.h"


/*
 @brief: 栈内优先数
 */
int isp(char c)
{
    switch (c) {
        case '#':
            return 0;
            break;
        case '(':
            return 1;
            break;
        case '*':
        case '/':
        case '%':
            return 5;
            break;
        case '+':
        case '-':
            return 3;
            break;
        case ')':
            return 6;
            break;
            
        default:
            return 0;
            break;
    }
}

/*
 @brief: 栈外优先数
 */
int icp(char c)
{
    switch (c) {
        case '#':
            return 0;
            break;
        case '(':
            return 6;
            break;
        case '*':
        case '/':
        case '%':
            return 4;
            break;
        case '+':
        case '-':
            return 2;
            break;
        case ')':
            return 1;
            break;
            
        default:
            return 0;
            break;
    }
}

void postFix(SeqStack<char>& s)
{
    rewind(stdin);
    
    char ch = '#', ch1, op;
    s.Push(ch);
    cin.get(ch);
    while (s.IsEmpty() == false && ch != '#')
    {
        if(isdigit(ch))
        {
            cout<<ch<<' ';
            cin.get(ch);
            if (ch=='\n')
                break;
            cin.get(ch);     //先读入一个空格
        }
        else
        {
            s.getTop(ch1);
            if(icp(ch) > isp(ch1))
            {
                s.Push(ch);
                cin.get(ch);
                if (ch=='\n')
                    break;
                cin.get(ch);
            }
            else if(icp(ch) < isp(ch1))
            {
                s.Pop(op);
                cout<<op<<' ';
            }
            else{
                s.Pop(op);
                if(op == '(')
                {
                    cin.get(ch);
                    if (ch=='\n')
                        break;
                    cin.get(ch);
                }
            }
        }
    }
    
    //操作符栈内剩余的操作符依次出栈并输出
    while(s.getSize()>1)
    {
        s.Pop(op);
        cout<<op<<' ';
    }
}

int main()
{
    SeqStack<char> stack;
    
    postFix(stack);
    
    return 0;
}
