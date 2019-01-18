# 数据结构项目文档

> 题目：8种排序算法的比较案例
>
> 指导教师：张颖
>
> 姓名：王亮
>
> 学号：1653340

---

[TOC]



## 一、题目分析

### 1. 项目简介

随机函数产生一百，一千，一万和十万个随机数，用快速排序，直接插入排序，冒泡排序，选择排序的排序方法排序，并统计每种排序所花费的排序时间和交换次数。其中，随机数的个数由用户定义，系统产生随机数。并且显示他们的比较次数。

### 2. 功能需求

请在文档中记录上述数据量下，各种排序的计算时间和存储开销，并且根据实验结果说明这些方法的优缺点。

### 3. 设计思路

本项目的问题是比较八种排序方法的优缺点。

为了更好的理解各个排序算法，我在提到的四种常用排序方法的基础上，还实现了希尔排序、堆排序、归并排序、基数排序等四种排序方法。本项目将对上述共八种排序算法进行不同数据量的测试并比较各自的性能。

具体的设计思路：

分别实现八个排序算法，每种算法实现过程中可能会需要实现一些特殊的数据结构。实现完成后使用不同的数据量进行测试，并分析各自性能。

## 二、设计

### 1. 数据结构设计

大多数排序算法只需要使用数组即可实现对数据的排序。

特殊的，

堆排序中需要用到最大堆；

LSD基数排序中需要用到静态链表。

### 2. 类的设计

#### 2.1 MaxHeap

在堆排序中用到。

```c++
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
```

#### 2.2 StaticList

在LSD基数排序中用到。

```c++
emplate <typename T>class StaticList{
    SLinkNode<T> *elem;
    int maxSize;
    int avil;//可用结点链链首下标
public:
    StaticList(int sz = defaultSize);
    ~StaticList();
    int Length();
    int Search(T x);
    int Locate(int i);
    int getData(int i);
    int getLink(int i);
    bool Append(T x);          //在表尾添加新结点
    bool Insert(int i, T x);   //在第i个结点后插入一个结点
    bool Remove(int i);
    bool IsEmpty();
    void output(int type = 0);
    void setLink(int location, int newLink);
    friend istream& operator >> (istream& in, StaticList<T> &stl){
        T data;
        while (!in.eof()){//在原链表后添加，与其他线性表不同
            in >> data;
            stl.Append(data);
        }
        return in;
    }
    friend ostream & operator<<(ostream &out, StaticList <T> &stl){
        int p = stl.elem[0].link;//elem[0]为附加头结点
        while(p != -1){
            cout << stl.elem[p].data << endl;
            p = stl.elem[p].link;
        }
        cout << endl;
        return out;
    }
};
```

### 3. 函数设计

#### 3.1 主函数

```flow
flow
st=>start: 开始
input=>inputoutput: 输入随机数个数
op=>operation: 产生随机数
op1=>operation: 使用不同的算法对随机数进行排序
e=>end: 结束
st->input->op->op1->e
```

#### 3.2 生成随机数

每次程序运行，输入随机数的个数，以当前时间为随机数种子，生成随机数，相关代码如下：

```c++
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
```

#### 3.3 排序前的准备

为了保证比较八种排序算法的结果可靠性，不同的排序算法要对相同的一组随机数进行排序。因此原始随机数数组是不应该被改变的，每次排序之前，将数据从原始随机数数组做一份拷贝，对拷贝数组进行排序。

排序过程中统计所用的时间和排序过程中发生交换的次数。

拷贝的过程不算在排序所用的时间之内。

```c++
copyNums(randoms, copyRandoms, num);
                
swapTimes = 0;
begin = clock();
//这里应该是各种排序算法的实现
finish = clock();
                
cout << "冒泡排序所用时间:    " << float(finish - begin)/CLOCKS_PER_SEC << "秒"<< endl;
cout << "冒泡排序交换次数:    " << swapTimes << endl << endl;
```



## 三、八种排序算法的实现

### 1. 冒泡排序

#### 1.1 原理

冒泡排序的名字很形象，实际实现是相邻两节点进行比较，大的向后移一个，经过第一轮两两比较和移动，最大的元素移动到了最后，第二轮次大的位于倒数第二个，依次进行。这是最基本的冒泡排序，还可以进行一些优化。

- 优化一：如果某一轮两两比较中没有任何元素交换，这说明已经都排好序了，算法结束，可以使用一个Flag做标记，默认为false，如果发生交互则置为true，每轮结束时检测Flag，如果为true则继续，如果为false则返回。

- 优化二：某一轮结束位置为j，但是这一轮的最后一次交换发生在lastSwap的位置，则lastSwap到j之间是排好序的，下一轮的结束点就不必是j--了，而直接到lastSwap即可。

#### 1.2 代码实现

```c++
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
```

### 2. 选择排序

#### 2.1 原理

遍历数组，遍历到i时，a0,a1...ai-1是已经排好序的，然后从i到n选择出最小的，记录下位置，如果不是第i个，则和第i个元素交换。此时第i个元素可能会排到相等元素之后，造成排序的不稳定。

#### 2.2 代码实现

```c++
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
```

### 3. 直接插入排序

#### 3.1 原理

遍历数组，遍历到i时，a0,a1...ai-1是已经排好序的，取出ai，从ai-1开始向前和每个比较大小，如果小于，则将此位置元素向后移动，继续先前比较，如果不小于，则放到正在比较的元素之后。可见相等元素比较是，原来靠后的还是拍在后边，所以插入排序是稳定的。

当待排序的数据基本有序时，插入排序的效率比较高，只需要进行很少的数据移动。

#### 3.2 代码实现

```c++
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
```

### 4. 希尔排序

#### 4.1 原理

希尔排序是对插入排序的优化，基于以下两个认识：1. 数据量较小时插入排序速度较快，因为n和n2差距很小；2. 数据基本有序时插入排序效率很高，因为比较和移动的数据量少。

因此，希尔排序的基本思想是将需要排序的序列划分成为若干个较小的子序列，对子序列进行插入排序，通过插入排序能够使得原来序列成为基本有序。这样通过对较小的序列进行插入排序，然后对基本有序的数列进行插入排序，能够提高插入排序算法的效率。

 希尔排序的划分子序列不是像归并排序那种的二分，而是采用的叫做增量的技术，例如有十个元素的数组进行希尔排序，首先选择增量为10/2=5，此时第1个元素和第（1+5）个元素配对成子序列使用插入排序进行排序，第2和（2+5）个元素组成子序列，完成后增量继续减半为2，此时第1个元素、第（1+2）、第（1+4）、第（1+6）、第（1+8）个元素组成子序列进行插入排序。这种增量选择方法的好处是可以使数组整体均匀有序，尽可能的减少比较和移动的次数，二分法中即使前一半数据有序，后一半中如果有比较小的数据，还是会造成大量的比较和移动，因此这种增量的方法和插入排序的配合更佳。

 希尔排序的时间复杂度和增量的选择策略有关，上述增量方法造成希尔排序的不稳定性。

#### 4.2 代码实现

```c++
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
                    swapTimes++;  //类似直接插入排序，同样不是严格意义的交换
                    j = j - gap;
                } while (j >= 0 && temp < randoms[j]);
                randoms[j + gap] = temp;
            }
        }
    } while (gap > 1);
}
```

### 5. 快速排序

#### 5.1 原理

任取待排序元素序列中的某个元素作为基准，按照该元素的排序码大小，将整个元素序列划分为左右两个子序列：左侧子序列中所有元素的排序码都小于基准元素的排序码，右侧子序列中所有元素的排序码都大于或等于基准元素的排序码，基准元素则排在这两个子序列中间。然后分别对这两个子序列重复施行上述方法，直到所有的元素都排在相应的位置上为止。

#### 5.2 代码实现

```c++
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
```

```c++
void quickSort(int* randoms, const int left, const int right, long long& swapTimes)
{
    if (left < right)
    {
        int pivotpos = partition(randoms, left, right, swapTimes);
        quickSort(randoms, left, pivotpos-1, swapTimes);
        quickSort(randoms, pivotpos+1, right, swapTimes);
    }
}
```

### 6. 堆排序

#### 6.1 原理

堆排序是把数组看作堆，第i个结点的孩子结点为第2*i+1和2*i+2个结点（不超出数组长度前提下），堆排序的第一步是建堆，然后是取堆顶元素然后调整堆。建堆的过程是自底向上不断调整达成的，这样当调整某个结点时，其左节点和右结点已经是满足条件的，此时如果两个子结点不需要动，则整个子树不需要动，如果调整，则父结点交换到子结点位置，再以此结点继续调整。

下述代码使用的最大堆，建立好堆后堆顶元素为最大值，此时取堆顶元素即使堆顶元素和最后一个元素交换，最大的元素处于数组最后，此时调整小了一个长度的堆，然后再取堆顶和倒数第二个元素交换，依次类推，完成数据的非递减排序。

堆排序的主要时间花在初始建堆期间，建好堆后，堆这种数据结构以及它奇妙的特征，使得找到数列中最大的数字这样的操作只需要O(1)的时间复杂度，维护需要logn的时间复杂度。堆排序不适宜于记录数较少的文件

#### 6.2 代码实现

```c++
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
```

### 7. 归并排序

#### 7.1 原理

归并排序是采用分治法（Divide and Conquer）的一个非常典型的应用。首先考虑下如何将将二个有序数列合并。这个非常简单，只要从比较二个数列的第一个数，谁小就先取谁，取了后就在对应数列中删除这个数。然后再进行比较，如果有数列为空，那直接将另一个数列的数据依次取出即可。这需要将待排序序列中的所有记录扫描一遍，因此耗费O(n)时间，而由完全二叉树的深度可知，整个归并排序需要进行 logn 次，因此，总的时间复杂度为O(nlogn)。

归并排序在归并过程中需 要与原始记录序列同样数量的存储空间存放归并结果，因此空间复杂度为O(n)。

归并算法需要两两比较，不存在跳跃，因此归并排序是一种稳定的排序算法。 

#### 7.2 代码实现

使用递归的方式，需要两个函数。

二路归并算法：

```c++
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
```

递归实现的归并排序：

```c++
void mergeSort(int* l1, int* l2, int left, int right, long long& swapTimes)
{
    if (left >= right) return;
    int mid = (left + right) / 2;
    mergeSort(l1, l2, left, mid, swapTimes);
    mergeSort(l1, l2, mid+1, right, swapTimes);
    merge(l1, l2, left, mid, right, swapTimes);
}
```

### 8. LSD基数排序

#### 8.1 原理

基数排序也可以看作一种桶排序，不断的使用不同的标准对数据划分到桶中，最终实现有序。基数排序的思想是对数据选择多种基数，对每一种基数依次使用桶排序。

基数排序的步骤：以整数为例，将整数按十进制位划分，从低位到高位执行以下过程。

    1. 从个位开始，根据0~9的值将数据分到10个桶桶，例如12会划分到2号桶中。
    
    2. 将0~9的10个桶中的数据顺序放回到数组中。

  重复上述过程，一直到最高位。

  上述方法称为LSD（Least significant digital），还可以从高位到低位，称为MSD。

#### 8.2 代码实现

辅助函数：

```c++
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
```

LSD基数排序算法：

```c++
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
```

## 四、测试结果

依次采用一百，一千，一万和十万个随机数对八种排序算法进行测试，统计每种排序所花费的排序时间和交换次数。

### 1. 100个随机数

![image-20181231132326048](https://ws4.sinaimg.cn/large/006tNc79gy1fzb45r4417j30rs15cwmd.jpg)

### 2. 1000个随机数

![image-20181231132736759](https://ws2.sinaimg.cn/large/006tNc79gy1fzb45qal2fj30rq15kwmc.jpg)

### 3. 10000个随机数

![image-20181231132904469](https://ws2.sinaimg.cn/large/006tNc79gy1fzb45qrh8pj30rs15mai5.jpg)

### 4. 100000个随机数

![image-20181231133240943](https://ws2.sinaimg.cn/large/006tNc79gy1fzb45ppzsvj30rs15qthf.jpg)

Windows操作系统下测试结果：

![image-20190101232502672](https://ws3.sinaimg.cn/large/006tNc79gy1fzb45p9nw4j30u015010n.jpg)

## 五、结果分析

实践发现，项目示例中的比较次数可能存在错误，但这并不影响我们比较各种排序算法的时间复杂度；而各种排序方案，除了桶排序和基数排序外，在空间上的差距并不大，所以我在后面会着重分析各种排序算法的时间复杂度。

经过使用不同规模的数据量对排序算法进行测试，可以发现：

> 总体来说，冒泡排序和直接插入排序整体的耗时最多。
>
> 其次是选择排序。
>
> 而剩下的希尔排序、快速排序、堆排序、归并排序和基数排序的用时相差不大，均表现较好。如果一定要在这五者之间比较孰优孰劣的话，希尔排序表现略微差了一点点。

这样的测试结果与我们在数据结构课程中所学到的各类排序算法的时间复杂度是吻合的：

> O(n^2): 冒泡排序、直接插入排序、选择排序
>
> O(n^7/6): 希尔排序
>
> O(n*log2(n)): 快速排序、堆排序、归并排序、基数排序

下面详细比较每种排序算法的性能和优缺点：

**冒泡排序：**

冒泡排序确实是一种简单易懂的算法。但是相对来说，冒泡排序的时间复杂度极为不理想。在最坏情况下，即要排序的数字完全是倒序排列，这样我们每执行一次循环，只能将一个数字放在正确的位置上，并且每次比较都需要交换两个数字，这是一笔非常大的开销，它的时间复杂度为O(n^2)。即使对于平均情况而言，它的时间复杂度也为O(n^2)。 

冒泡排序对空间的要求不高，既不需要辅助数组，也不执行递归调用，所以它的空间复杂度为O(1)。  
由于我们只在后一个元素大于前一个元素的前提下，才会交换两个元素的位置，所以冒泡排序是一种稳定的排序算法。

**选择排序：**

由于省掉了每次比较后的交换过程（实际上选择排序总共只执行(n-1)交换），所以面对相同的数据量，选择排序远快于冒泡排序，这一点在前面的展示中也体现出来。但是，虽然速度快了不少，选择排序与冒泡排序的时间复杂度是一样的。在最坏情况下，时间复杂度为O(n^2)，平均情况下时间复杂度也为O(n^2)。  
选择排序的空间复杂度也为O(1)，同样不要辅助数组和递归调用。  
由于选择排序不能保证在交换两个元素时不破坏相同元素的前后顺序，所以是不稳定的。  

**直接插入排序：**

直接插入排序的时间复杂度与前两种排序方法一致，最坏情况下为O(n^2)，平均情况下为O(n^2)。空间复杂度的情况也一样，为O(1)。  
直接插入排序是顺序地选择元素并与前一个元素比较，并且只在后一个元素小于前一个元素时才进行交换，所以是稳定的。

**希尔排序：**

希尔排序通过比较两个间隔较远的元素，使得一次交换能够消除多个逆序，大大提高了运行速度。但是，根据使用的增量序列的不同，得到的时间界也有所不同。可以证明：  

> 使用希尔增量时希尔排序的最坏情形运行时间为O(n^2)

如果我们换一组增量，如使用Hibbard增量，这种增量形如1, 3, 7, ..., 2^k-1，在这种增量序列下最坏的时间复杂度为O(n^3/2)，这是经过严格证明的；而平均情况下的时间复杂度无法进行证明，但是在实践中人们大致上估计出了其平均时间复杂度为O(n^5/4)。如果使用Sedgewick增量，平均时间复杂度可以进一步优化到O(n^7/6)，最坏时间复杂度为O(n^4/3)。  
希尔排序的空间复杂度为O(1)。  
由于希尔排序每次比较、交换的两个元素位置间隔较远，不能保证不破坏相同元素的前后顺序，所以是不稳定的。

**快速排序：**

快速排序在最坏的情况下，时间复杂度为O(n^2)；在平均情况下，时间复杂度可以达到O(nlogn)，可以说是十分理想了。  
由于快速排序为递归函数，所以需要消耗栈空间。在最坏情况下，空间复杂度为O(n)，此时完全是按照{1, n-1}的数量划分数组；在平均情况下，空间复杂度为O(logn)。  
快速排序在每次遍历待排序数组时，都是由两头向中间移动，交换元素时可能破坏相同元素的前后顺序，所以是不稳定的。

**堆排序：**

对于时间复杂度的分析也是容易的：建堆的时间复杂度为O(n)；每次下滤的时间复杂度为O(logn)，删除的过程共执行(n-1)次下滤，则总的时间复杂度为O(nlogn)。在最坏情况下和平均情况下的时间复杂度都是如此。  
堆排序不是递归算法，也不需要额外的存储空间（辅助数组），所以其空间复杂度为O(1)。  
由于无法保证相同元素的出堆顺序，所以堆排序是不稳定的排序算法。

**归并排序：**

归并操作的时间复杂度是极为优秀的。由于我们将子数组细分到只有一个元素为止，所以实质上不存在最坏情况与平均情况之分：因为根本没有**排序**这个操作。将待排序数组进行划分的时间复杂度为O(logn)，而合并两个有序数组的时间复杂度为O(n)，且一次合并对应一次划分，所以总的时间复杂度为O(nlogn)。  
归并操作的辅助数组占用的空间为O(n)，递归时消耗的栈空间为O(logn)，所以其总的空间复杂度为O(n)。可见，在已给出的几种算法中，归并排序的空间复杂度是最高的。但是相对的，归并排序在实践中的速度仅次于快速排序，是一种十分高效、容易理解的排序算法。  
由于归并排序可以保证在合并操作时，两个分别处于不同数组的相同元素的前后顺序保持不变，所以是稳定的。

**基数排序：**

基数排序的时间复杂度为O(d(n+r))，其中d为最大元素的位数，r为基数的个数，这里为10(0~9)。  
基数排序的空间需求在于两个辅助数组，分别用于储存中间过程的结果和每个基数对应的开始位置，故空间复杂度为O(n+r)。  
由于我们保证了前i位有序的数字的相对位置不变，所以基数排序是一种稳定的排序算法。

## 六、总结

| 排序方式     | 平均时间复杂度 | 最坏时间复杂度 | 空间复杂度 | 稳定性 |
| ------------ | -------------- | -------------- | ---------- | ------ |
| 冒泡排序     | O(n^2)         | O(n^2)         | O(1)       | 稳定   |
| 选择排序     | O(n^2)         | O(n^2)         | O(1)       | 不稳定 |
| 直接插入排序 | O(n^2)         | O(n^2)         | O(1)       | 稳定   |
| 希尔排序     | O(n^7/6)       | O(n^4/3)       | O(1)       | 不稳定 |
| 快速排序     | O(nlogn)       | O(n^2)         | O(logn)    | 不稳定 |
| 堆排序       | O(nlogn)       | O(nlogn)       | O(1)       | 不稳定 |
| 归并排序     | O(nlogn)       | O(nlogn)       | O(n)       | 稳定   |
| 基数排序     | O(d(n+r))      | O(d(n+r))      | O(n+r)     | 稳定   |