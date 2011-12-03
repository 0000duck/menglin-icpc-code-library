/*
  Name: Quick Sort
  Copyright: LogicalMars Libarary
  Author: Logical Mars
  Date: 12-10-08 15:00
*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
long n;
long s[1000];
void swap(long &sa,long &sb)
{
    long temp=sa;
    sa=sb;
    sb=temp;
}
void qsort(long h,long t)
{
    if (h>=t) return;
    long i=h,j=t,mid=s[h+rand()%(t-h)];
    do
    {
        while (s[i]<mid) i++;
        while (s[j]>mid) j--;
        if (i<=j) {swap(s[i],s[j]);i++;j--;}
    }while (i<=j);
    qsort(h,j);qsort(i,t);
}
int main()
{
    srand(time(0));
    freopen("qsort.in","r",stdin);
    freopen("qsort.out","w",stdout);
    scanf("%ld",&n);
    long i;
    for (i=1;i<=n;i++) scanf("%ld",&s[i]);
    qsort(1,n);
    for (i=1;i<=n;i++) printf("%ld ",s[i]);
    return 0;
}
    
