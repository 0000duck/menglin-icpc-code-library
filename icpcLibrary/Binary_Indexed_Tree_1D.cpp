/*
  Name: ��״���� 
  Copyright: LogicalMars Library
  Author: LogicalMars   
  Date: 16-10-08 22:14
  Description: ������ͣ�1 �� X 
*/
#include <stdio.h>
#include <string.h> 
const long maxn=10000;
long c[maxn];
long lowbit(long x)
{
    return x & (x ^ (x-1));
}
void add(long x,long a) //�Ե�X��������a 
{
    while (x<=maxn)
    {
        c[x]+=a;
        x+=lowbit(x);
    }
}
long sum(long x)        //��ǰX��ĺ� 
{
    long re=0;
    while (x>0)
    {
        re+=c[x];
        x-=lowbit(x);
    }
    return re;
}

