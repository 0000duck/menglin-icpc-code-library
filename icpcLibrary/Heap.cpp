/*
  Name: Heap
  Copyright: LogicalMars Library
  Author: LogicalMars
  Date: 13-10-08 12:52
  Description: 小根堆，根节点始终是堆中的最小值，O(logn)的插入和删除复杂度 
*/

#include <iostream.h>
int len;   //记录d中目前的数据数目
long dele()//返回最小值，并删除之 
{
  long re=d[1];
  long y=d[len];
  len--;
  int i=1;
  while (i<len)
   {
    int j=i*2;
    while (j<len && d[j]>d[j+1]) j++;
    if (d[j]<y) {
                 d[i]=d[j];
                 i=j;
                }
         else break;
   }
  if (i<len) d[i]=y;
  return re;
}
void add(long x)
{
  len++;
  long i=len;
  while (i>1)
   {
    if (d[i/2]>x)    {
                      d[i]=d[i/2];
                      i/=2;
                     }
            else    break;
   }
  if (i>0) d[i]=x;
}
