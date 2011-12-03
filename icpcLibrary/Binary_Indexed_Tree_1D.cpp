/*
  Name: 树状数组 
  Copyright: LogicalMars Library
  Author: LogicalMars   
  Date: 16-10-08 22:14
  Description: 快速求和，1 ～ X 
*/
#include <stdio.h>
#include <string.h> 
const long maxn=10000;
long c[maxn];
long lowbit(long x)
{
    return x & (x ^ (x-1));
}
void add(long x,long a) //对第X个数加上a 
{
    while (x<=maxn)
    {
        c[x]+=a;
        x+=lowbit(x);
    }
}
long sum(long x)        //求前X项的和 
{
    long re=0;
    while (x>0)
    {
        re+=c[x];
        x-=lowbit(x);
    }
    return re;
}

