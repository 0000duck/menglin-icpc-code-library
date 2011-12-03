/*
  Name: Heap
  Copyright: LogicalMars Library
  Author: LogicalMars
  Date: 13-10-08 12:52
  Description: С���ѣ����ڵ�ʼ���Ƕ��е���Сֵ��O(logn)�Ĳ����ɾ�����Ӷ� 
*/

#include <iostream.h>
int len;   //��¼d��Ŀǰ��������Ŀ
long dele()//������Сֵ����ɾ��֮ 
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
