
//
//  maxHeap.hpp
//  DataStructure_10
//
//  Created by Leon Wang on 2018/12/24.
//  Copyright © 2018 Leon. All rights reserved.
//

#ifndef MAXHEAP_H
#define MAXHEAP_H
#include <iostream>
#include <cassert>
using namespace std;
const int DefaultSize=50;

template <typename E/*,class K*/>class MaxHeap{    // K为关键码的数据类型，E为记录的结构类型
public:
    MaxHeap(int sz = DefaultSize);//构造函数：建立空堆
    MaxHeap(E arr[], int n);    //构造函数：通过一个数组建堆
    ~MaxHeap()    {
        delete []heap;
    }
    bool Insert(const E &x);
    bool RemoveMax(E &x);
    bool IsEmpty()const{
        return currentSize == 0;
    }
    bool IsFull()const{
        return currentSize == maxHeapSize;
    }
    void MakeEmpty(){
        currentSize = 0;
    }
    void Swap(int i, int j){
        E tmp = heap[i];
        heap[i] = heap[j];
        heap[j] = tmp;
    }

    void output(){//自定义函数，顺序输出最大堆元素
        for(int i = 0; i<currentSize; i++)
            cout<<heap[i]<<" ";
        cout<<endl;
    }
    void siftDown(int start, int m);//从start到m下滑调整成为最大堆
    void siftDown(int start, int m, long long& swapTimes);//从start到m下滑调整成为最大堆
    void siftUp(int start);            //从start到0上滑调整成为最大堆

private:
    E *heap;                        //存放最大堆中元素的数组
    int currentSize;                //最大堆中当前元素个数
    int maxHeapSize;                //最大堆最多允许元素个数
};

// 构造函数：建立空堆
template <typename E/*,class K*/>MaxHeap<E/*, K*/>::MaxHeap(int sz){
    maxHeapSize = (DefaultSize < sz) ? sz : DefaultSize;
    heap = new E[maxHeapSize];
    assert(heap);
    currentSize = 0;
}

// 构造函数：通过一个数组建堆，只输入数据，不进行调整
template <typename E/*,class K*/>MaxHeap<E/*, K*/>::MaxHeap(E arr[], int n){
    maxHeapSize = (DefaultSize < n) ? n : DefaultSize;
    heap = new E[maxHeapSize];
    assert(heap);
    for (int i = 0; i < n; i++ ){
        heap[i] = arr[i];
    }
    currentSize = n;
//    int currentPos = (currentSize-2)/2;        //找最初调整位置:最后分支结点
//    while (currentPos >= 0){                    //自底向上逐步扩大形成堆
//        siftDown(currentPos, currentSize -1);    //局部自上向下下滑调整
//        currentPos--;                            //再向前换一个分支结点
//    }
}


//私有函数：最大堆的下滑调整算法
template <typename E/*,class K*/>void MaxHeap<E/*, K*/>::siftDown(int start, int m){
    int i = start, j = 2*i+1;//j是i的左子女位置
    E temp = heap[i];
    while (j <= m){//检查是否到最后位置
        //让j指向两子女中的小者
        if (j < m && heap[j] < heap[j+1]){
            j++;
        }
        if (temp >= heap[j]){
            break;
        }
        else{
            heap[i] = heap[j];
            i = j;
            j = 2*j+1;
        }
    }
    heap[i] = temp;    //回放temp中暂存的元素
}

//私有函数：最大堆的下滑调整算法，并统计调整过程中的交换次数
template <typename E/*,class K*/>void MaxHeap<E/*, K*/>::siftDown(int start, int m, long long& swapTimes){
    int i = start, j = 2*i+1;//j是i的左子女位置
    E temp = heap[i];
    while (j <= m){//检查是否到最后位置
        //让j指向两子女中的小者
        if (j < m && heap[j] < heap[j+1]){
            j++;
        }
        if (temp >= heap[j]){
            break;
        }
        else{
            heap[i] = heap[j];  swapTimes++;
            i = j;
            j = 2*j+1;
        }
    }
    heap[i] = temp;    //回放temp中暂存的元素
}

// 私有函数：最大堆的上滑调整算法
template <typename E/*,class K*/>void MaxHeap<E/*, K*/>::siftUp(int start){
    int j = start, i = (j-1)/2;
    E temp = heap[j];
    while (j > 0){ //沿父结点路径向上直达根
        if (heap[i] >= temp)        {
            break;
        }
        else{
            heap[j] = heap[i];
            j = i;
            i = (i-1)/2;
        }
    }
    heap[j] = temp;    //回放temp中暂存的元素
}

// 公共函数: 将x插入到最大堆中
template <typename E/*,class K*/>bool MaxHeap<E/*, K*/>::Insert(const E &x){
    if (currentSize == maxHeapSize){    //堆满
        cerr << "Heap Full" << endl;
        return false;
    }
    heap[currentSize] = x;    //插入
    siftUp(currentSize);    //向上调整
    currentSize++;            //堆计数加1
    return true;
}

// 公共函数：最大堆的删除算法
template <typename E/*,class K*/>bool MaxHeap<E/*, K*/>::RemoveMax(E &x){
    if (!currentSize){    //堆空, 返回false

        cout << "Heap empty" << endl;
        return false;
    }
    x = heap[0];        // 返回最大元素
    heap[0] = heap[currentSize-1];    //最后元素填补到根结点
    currentSize--;
    siftDown(0, currentSize-1);        //自上向下调整为堆
    return true;
}

#endif
