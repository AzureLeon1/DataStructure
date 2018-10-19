//
//  main.cpp
//  DataStructure_4
//
//  Created by Leon Wong on 2018/10/16.
//  Copyright © 2018 Leon. All rights reserved.
//


//将中缀表达式转换成为后缀表达式

//题目文档中减号格式有问题

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

/*
 *@brief: 判断是否是数字
 */
bool isDigit(char& ch, string& tempDigit, bool& haveChecked)
{
    if(ch == '-' || ch == '+')
    {
        if(haveChecked)
            return false;
        tempDigit += ch;
        cin.get(ch);
    }
    while(isdigit(ch) || ch=='.')
    {
        tempDigit += ch;
        cin.get(ch);
    }
    
    if(tempDigit.length() > 0 && tempDigit != "-" && tempDigit != "+")
        return true;
    else
    {
        if(tempDigit == "-" || tempDigit == "+")
            haveChecked = true;
        return false;
    }
}

void postFix(SeqStack<char>& s)
{
    cout<<"请输入中缀表达式（每个字符间用空格分隔，结尾没有多余的空格）："<<endl;
    bool haveCheckedNeviOrPosi = false;
    string tempDigit = "";
    char ch = '#', ch1, op;
    s.Push(ch);
    cin.get(ch);
    while (s.IsEmpty() == false)
    {
        //清空tempDigit
        tempDigit = "";
        
        if( isDigit(ch, tempDigit, haveCheckedNeviOrPosi) )
        {
            cout<<tempDigit;

            if (ch=='\n')
            {
                if(s.getSize()>1)
                    cout<<' ';
                break;
            }
            cout<<' ';
            cin.get(ch);
        }
        else
        {
            if(tempDigit == "-")
                ch = '-';
            if(tempDigit == "+")
                ch = '+';
            
            s.getTop(ch1);
            if(icp(ch) > isp(ch1))
            {
                s.Push(ch);
                
                if(ch=='-' || ch=='+')
                    haveCheckedNeviOrPosi = false;
                
                if(ch != '-' && ch != '+')
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
        cout<<op;
        if(s.getSize()>1)
            cout<<' ';
    }
}

int main()
{
    SeqStack<char> stack;
    
    postFix(stack);
    
    return 0;
}
