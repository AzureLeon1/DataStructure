//
//  main.cpp
//  DataStructure_9-2
//
//  Created by Leon Wang on 2018/12/15.
//  Copyright © 2018 Leon. All rights reserved.
//



//来源自网络

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
struct data
{
    int b,lenth;
};
typedef struct node *Node;
struct node
{
    struct data Next[101];
    int Output,O;
    struct data From[101];
    int Input,I;
};

int TopSort(Node V,int n);
int* ImportantRode(Node,int,int );

int main()
{
    //std::cout<<"请输入："<<std::endl;
    struct node V[101];
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1; i<=n; i++)
    {
        V[i].Input =0;
        V[i].Output =0;
    }
    while(m--)
    {
        int disk1,disk2,lenth;
        scanf("%d%d%d",&disk1,&disk2,&lenth);
        V[disk1].Next[++V[disk1].Output].b =disk2;
        V[disk1].Next[V[disk1].Output ].lenth=lenth;
        V[disk2].From[++V[disk2].Input].b=disk1;
        V[disk2].From[V[disk2].Input].lenth=lenth;
    }
    for(int i=1;i<=n;i++){
        V[i].I =V[i].Input ;
        V[i].O=V[i].Output ;
    }
    int Coast =TopSort(V,n);
    return 0;
}

int TopSort(Node V,int n)
{
    int Earliest[101]= {0};
    while(1)
    {
        int flag=0;
        for(int i=1; i<=n; i++)
        {
            if(0==V[i].Input)
            {
                //              printf("{%d}",i);
                flag=1;
                for(int j=1; j<=V[i].Output ; j++)
                {
                    if(Earliest[V[i].Next[j].b]<Earliest[i]+V[i].Next[j].lenth)
                    {
                        Earliest[V[i].Next[j].b]=Earliest[i]+V[i].Next[j].lenth;
                    }
                    V[V[i].Next[j].b].Input-=1;
                }
                V[i].Input =-1;
            }
        }
        if(!flag)break;
    }
    //  for(int i=0;i<n;i++){
    //      printf("[%d|%d->%d]",V[i].Input,V[i].Output,Earliest[i] );
    //  }
    int max=0,index;
    for(int i=1; i<=n; i++)
    {
        if(V[i].Input >0)
        {
            max=0;
            break;
        }
        if(Earliest[i]>max)
        {
            max=Earliest[i];
            index=i;
        }
    }
    printf("%d",max);
    if(max==0)return 0;
    int *Latest=ImportantRode(V,max,n);
    for(int i=1; i<=n; i++)
    {
        //      printf("{%d,%d}",Earliest[i],Latest[i]);
        if(Latest[i]==Earliest[i])
        {
            for(int j=V[i].O; j>0; j--)
            {
                if(Latest[V[i].Next[j].b]==Latest[i]+V[i].Next[j].lenth )
                {
                    printf("\n%d->%d",i,V[i].Next[j].b);
                }
            }
        }
    }
    return max;
}
int* ImportantRode(Node V,int max,int n)
{
    int*Latest=(int*)malloc(sizeof(int)*101);
    for(int i=1; i<=n; i++)
    {
        Latest[i]=max;
    }
    while(1)
    {
        int flag=0;
        for(int i=1; i<=n; i++)
        {
            if(0==V[i].Output)
            {
                flag=1;
                for(int j=1; j<=V[i].I; j++)
                {
                    if(Latest[V[i].From[j].b]>Latest[i]-V[i].From[j].lenth)
                    {
                        Latest[V[i].From[j].b]=Latest[i]-V[i].From[j].lenth;
                    }
                    V[V[i].From[j].b].Output  -=1;
                }
                V[i].Output   =-1;
            }
        }
        if(!flag)break;
    }
    
    
    return Latest;
}
