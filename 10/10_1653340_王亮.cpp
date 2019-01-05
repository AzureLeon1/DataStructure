//
//  main.cpp
//  DataStructure_10
//
//  Created by Leon Wang on 2018/12/23.
//  Copyright © 2018 Leon. All rights reserved.
//

//项目简介：
//随机函数产生一百，一千，一万和十万个随机数，用快速排序，直接插入排序，冒泡排序，选择排序的排序方法排序，并统计每种排序所花费的排序时间和交换次数。其中，随机数的个数由用户定义，系统产生随机数。并且显示他们的比较次数。
//
//请在文档中记录上述数据量下，各种排序的计算时间和存储开销，并且根据实验结果说明这些方法的优缺点。

#include <iostream>
#include <ctime>
#include "MaxHeap.h"
#include "StaticLIst.h"

using namespace std;


/*
 *@brief: 显示功能选项菜单
 */
void showMenu()
{
    cout << "**\t\t排序算法比较\t\t**" << endl;
    cout << "==========================================" << endl;
    cout << "**\t\t1 --- 冒泡排序\t\t**" << endl;
    cout << "**\t\t2 --- 选择排序\t\t**" << endl;
    cout << "**\t\t3 --- 直接插入排序\t**" << endl;
    cout << "**\t\t4 --- 希尔排序\t\t**" << endl;
    cout << "**\t\t5 --- 快速排序\t\t**" << endl;
    cout << "**\t\t6 --- 堆排序\t\t**" << endl;
    cout << "**\t\t7 --- 归并排序\t\t**" << endl;
    cout << "**\t\t8 --- 基数排序\t\t**" << endl;
    cout << "**\t\t9 --- 退出程序\t\t**" << endl;
    cout << "==========================================" << endl << endl;
}


/*
 *@brief: 生成随机数，数组的大小为num，每个元素的值在0～num之间
 */
int* generateRandoms(int n)
{
    int* r = new int[n];

    srand(int(time(0)));
    for(int i = 0; i < n; i++)
        r[i] = rand() % n;

    return r;
}

/*
 *@brief: 将copyRandoms数组置为randoms数组的拷贝
 */
void copyNums(int* origin, int* copy, int num)
{
    for (int i = 0; i < num; i++)
        copy[i] = origin[i];
}



//=================排序算法部分====================================

void bubbleSort(int* randoms, int num, long long& swapTimes)
{
    for (int i = 1; i < num; i++)
        for (int j = num - 1; j >= i; j--)
            if (randoms[j-1] > randoms[j])
            {
                swap(randoms[j-1], randoms[j]);
                swapTimes++;
            }
}

void selectSort(int* randoms, int num, long long& swapTimes)
{
    for (int i = 0; i < num-1; i++)
    {
        int k = i;
        for (int j = i+1; j <= num-1; j++)
        {
            if (randoms[j] < randoms[k])
                k = j;
        }
        if (k != i)
        {
            swap(randoms[i], randoms[k]);
            swapTimes++;
        }
    }
}


void insertSort(int* randoms, int num, long long& swapTimes)
{
    int temp, i, j;
    for (i = 1; i < num; i++)
    {
        if (randoms[i] < randoms[i-1])
        {
            temp = randoms[i];
            j = i-1;
            do{
                randoms[j+1] = randoms[j];
                swapTimes++;       //不是严格意义上的交换。把该元素前比它大的元素整体后移一位，然后插入该元素。
                j--;
            } while(j >= 0 && temp < randoms[j]);
            randoms[j+1] = temp;
        }
    }
}

void shellSort(int* randoms, int num, long long& swapTimes)
{
    int i, j, gap = num;
    int temp;
    do{
        gap = gap/3 + 1;
        for (i = gap; i < num; i++)
        {
            if (randoms[i] < randoms[i-gap])
            {
                temp = randoms[i];
                j = i - gap;
                do {
                    randoms[j + gap] = randoms[j];
                    swapTimes++;         //同样不是严格意义的交换
                    j = j - gap;
                } while (j >= 0 && temp < randoms[j]);
                randoms[j + gap] = temp;
            }
        }
    } while (gap > 1);
}

/*
 *@brief: 快速排序的辅助函数，功能是实现划分，并返回基准元素的位置。快排的基准选择每次最左边的元素。
 */
int partition(int* nums, const int low, const int high, long long& swapTimes)
{
    int pivotpos = low;
    int pivot = nums[low];
    for (int i = low+1; i <= high; i++)
    {
        if (nums[i] < pivot)
        {
            pivotpos++;
            if (pivotpos != i)
            {
                swap(nums[pivotpos], nums[i]);
                swapTimes++;
            }
        }
    }
    nums[low] = nums[pivotpos]; nums[pivotpos] = pivot;
    swapTimes++;

    return pivotpos;
}

void quickSort(int* randoms, const int left, const int right, long long& swapTimes)
{
    if (left < right)
    {
        int pivotpos = partition(randoms, left, right, swapTimes);
        quickSort(randoms, left, pivotpos-1, swapTimes);
        quickSort(randoms, pivotpos+1, right, swapTimes);
    }
}

void heapSort(MaxHeap<int>* h, int num, long long& swapTimes)
{
    for (int i = (num-2)/2; i >= 0; i--)
    {
        h->siftDown(i, num-1, swapTimes);
    }
    for (int i = num-1; i >= 0; i--)
    {
        h->Swap(0, i);
        swapTimes++;
        h->siftDown(0, i-1, swapTimes);
    }
}

void merge(int* l1, int* l2, const int left, const int mid, const int right, long long& swapTimes)
{
    for (int k = left; k <= right; k++)        //复制出辅助数组
    {
        l2[k] = l1[k];
    }
    int s1 = left, s2 = mid+1, t = left;
    while(s1 <= mid && s2 <= right)
    {
        if(l2[s1] <= l2[s2]) l1[t++] = l2[s1++];
        else l1[t++] = l2[s2++];

        swapTimes++;
    }
    while(s1 <= mid)
    {
        l1[t++] = l2[s1++];
        swapTimes++;
    }
    while (s2 <= right)
    {
        l1[t++] = l2[s2++];
        swapTimes++;
    }
}

void mergeSort(int* l1, int* l2, int left, int right, long long& swapTimes)
{
    if (left >= right) return;
    int mid = (left + right) / 2;
    mergeSort(l1, l2, left, mid, swapTimes);
    mergeSort(l1, l2, mid+1, right, swapTimes);
    merge(l1, l2, left, mid, right, swapTimes);
}


/*
 *@brief: 获得数字num的第i位数字（从最低位起）
 */
int getDigit(int num, int i)
{
    int result;
    for (int cnt = 0; cnt < i-1; cnt++)
        num /= 10;
    result = num % 10;
    return result;
}

/*
 *@brief: 基数排序，d表示有多少个基数位，即进行多少轮分配和收集。此处d是随机数中最大数字的位数
 */
void radixSort (StaticList<int>* list, const int d, long long& swapTimes)
{
    int radix = 10;        //每个基数（即每一位）所有可能的取值是0～9，共10种
    int rear[radix], front[radix];
    int i, j, k, last, current, n = list->Length();
    for (i = 0; i < n; i++)
    {
        list->setLink(i, i+1);
    }
    list->setLink(n, 0);
    current = 1;
    for(i = 1; i <= d; i++)
    {
        for(j = 0; j < radix; j++)
        {
            front[j] = 0;
        }
        while (current != 0)
        {
            k = getDigit(list->getData(current), i);         //取当前检测元素的倒数第i位数
            if(front[k] == 0) front[k] = current;
            else list->setLink(rear[k], current);
            //swapTimes++;
            rear[k] = current;
            current = list->getLink(current);
        }
        j = 0;
        while (front[j] == 0) j++;
        current = front[j];
        list->setLink(0, current);
        last = rear[j];
        for (k = j + 1; k < radix; k++)
        {
            if(front[k] != 0)
            {
                list->setLink(last, front[k]);
                last = rear[k];
            }
        }
        list->setLink(last, 0);
    }
}





//===============================================================





/*
 *@brief: 程序主循环
 */
void run(int* randoms, int* copyRandoms, int num)
{
    //int test;
    int choice, digit, temp;
    MaxHeap<int>* h;    //用于堆排序
    int* tempNums;      //用于归并排序
    StaticList<int>* list;   //用于基数排序
    clock_t begin, finish;
    long long swapTimes;
    while (1)
    {
        cout << "请选择排序算法：";
        cin >> choice;

        switch (choice)
        {
            case 1:
                //冒泡排序
                copyNums(randoms, copyRandoms, num);

                swapTimes = 0;
                begin = clock();
                bubbleSort(copyRandoms, num, swapTimes);
                finish = clock();

                cout << "冒泡排序所用时间:    " << float(finish - begin)/CLOCKS_PER_SEC << "秒"<< endl;
                cout << "冒泡排序交换次数:    " << swapTimes << endl << endl;
                break;
            case 2:
                //选择排序
                copyNums(randoms, copyRandoms, num);

                swapTimes = 0;
                begin = clock();
                selectSort(copyRandoms, num, swapTimes);
                finish = clock();

                cout << "选择排序所用时间:    " << float(finish - begin)/CLOCKS_PER_SEC << "秒"<< endl;
                cout << "选择排序交换次数:    " << swapTimes << endl << endl;

                break;
            case 3:
                //直接插入排序
                copyNums(randoms, copyRandoms, num);

                swapTimes = 0;
                begin = clock();
                insertSort(copyRandoms, num, swapTimes);
                finish = clock();

                cout << "直接插入排序所用时间:    " << float(finish - begin)/CLOCKS_PER_SEC << "秒"<< endl;
                cout << "直接插入排序交换次数:    " << swapTimes << endl << endl;

                break;
            case 4:
                //希尔排序
                copyNums(randoms, copyRandoms, num);

                swapTimes = 0;
                begin = clock();
                shellSort(copyRandoms, num, swapTimes);
                finish = clock();

                cout << "希尔排序所用时间:    " << float(finish - begin)/CLOCKS_PER_SEC << "秒"<< endl;
                cout << "希尔排序交换次数:    " << swapTimes << endl << endl;

                break;
            case 5:
                //快速排序
                copyNums(randoms, copyRandoms, num);

                swapTimes = 0;
                begin = clock();
                quickSort(copyRandoms, 0, num-1, swapTimes);
                finish = clock();

                cout << "快速排序所用时间:    " << float(finish - begin)/CLOCKS_PER_SEC << "秒"<< endl;
                cout << "快速排序交换次数:    " << swapTimes << endl << endl;

                break;
            case 6:
                //堆排序
                //copyNums(randoms, copyRandoms, num);
                h = new MaxHeap<int>(copyRandoms, num);

                swapTimes = 0;

                begin = clock();
                heapSort(h, num, swapTimes);
                finish = clock();

                cout << "堆排序所用时间:    " << float(finish - begin)/CLOCKS_PER_SEC << "秒"<< endl;
                cout << "堆排序交换次数:    " << swapTimes << endl << endl;

                delete h;
                break;
            case 7:
                //归并排序
                copyNums(randoms, copyRandoms, num);
                tempNums = new int[num];

                swapTimes = 0;
                begin = clock();
                mergeSort(copyRandoms, tempNums, 0, num-1, swapTimes);
                finish = clock();

                cout << "归并排序所用时间:    " << float(finish - begin)/CLOCKS_PER_SEC << "秒"<< endl;
                cout << "归并排序比较次数:    " << swapTimes << endl << endl;

                delete[] tempNums;
                break;
            case 8:
                //基数排序
                //copyNums(randoms, copyRandoms, num);
                list = new StaticList<int>(num+1);
                for(int cnt = 0; cnt < num; cnt++)
                    list->Append(randoms[cnt]);
                digit = 0; temp = num;
                while (temp!=0)
                {
                    temp /= 10;
                    digit++;
                }

                swapTimes = 0;
                begin = clock();
                radixSort(list, digit, swapTimes);
                finish = clock();

                cout << "基数排序所用时间:    " << float(finish - begin)/CLOCKS_PER_SEC << "秒"<< endl;
                cout << "基数排序交换次数:    " << swapTimes << endl << endl;

//                //check the result
//                test=list->getLink(0);
//                for (int c=0; c<num;c++)
//                {
//                    cout << c << "   " << test << "   " << list->getData(test) << endl;
//                    test = list->getLink(test);
//                }

                delete list;
                break;
            case 9:
                //退出程序
                return;
                break;


            default:
                break;
        }

    }
}

int main(int argc, const char * argv[])
{
    showMenu();

    cout << "请输入要产生的随机数的个数：";
    int num;
    cin >> num;
    cout << endl;

    int* randoms = generateRandoms(num);        //大小为num的随机数数组
    int* copyRandoms = new int[num];            //大小为num的数组，是randoms数组的拷贝版本，用于排序

    run(randoms, copyRandoms, num);

    delete[] randoms;
    return 0;
}
