/*
  Name: ����� 
  Copyright: LogicalMars Library
  Author: LogicalMars
  Date: 17-10-08 10:39
  Description: ʹ���ڽӱ����ѷ� 
*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
FILE *fin=fopen("plan.in","r"),*fout=fopen("plan.out","w");
const long maxn=3010;                   //��󶥵��� 
const long maxlong=0x7fffffff/2;
long n;                        
long f[maxn][maxn];                     //�洢���� 
long map[maxn][maxn];                   //�������� 
struct linktype
{
    long key;
    linktype *next,*other;              //nextΪ����� otherΪ����� 
}*link[maxn];
void add(long x,long y)                 //���һ����<x,y>���ڽӱ��� 
{
    linktype *p=new linktype;
    p->key=y;
    p->next=p->other=NULL;
    p->next=link[x]->next;
    link[x]->next=p;
    
    linktype *q=new linktype;
    q->key=x;
    q->next=q->other=NULL;
    q->next=link[y]->other;
    link[y]->other=q;
}
void init()
{
    memset(f,0,sizeof(f));
    memset(map,0,sizeof(map));    
    long i;
    //���룬�˴�������Ϊn+2 
    //
    // 
    for (i=1;i<=n+2;i++) 
    {
        link[i]=new linktype;
        link[i]->key=0;
        link[i]->next=link[i]->other=NULL;
    }
    //����ߣ�ע��addֻ�Ǽӱ� 
    
}
long last[maxn],d[maxn];

void maxflow()                            //������1ΪԴ����n+2Ϊ�������� 
{
    long i,j,h,t;
    while (1)
    {
        memset(last,0,sizeof(last));
        memset(d,0,sizeof(d));
        h=t=1;
        d[1]=1;
        last[1]=1;
        do
        {
            i=d[h];
            linktype *p=link[i]->next;
            while (p)
            {
                j=p->key;
                if (last[j]==0 && f[i][j]<map[i][j])
                {
                    last[j]=i;
                    t++;d[t]=j;
                }
                p=p->next;
            }
            p=link[i]->other;
            while (p)
            {
                j=p->key;
                if (last[j]==0 && f[j][i]>0) 
                {
                    last[j]=-i;
                    t++;d[t]=j;                
                }
                p=p->next;
            }
            h++;                    
        }while (last[n+2]==0 && h<=t);
        if (last[n+2]==0) break;
        long delta=maxlong;
        i=n+2;
        do
        {
            j=i;i=labs(last[j]);
            long x;
            if (last[j]>=0) x=map[i][j]-f[i][j];
            else x=f[j][i];
            if (x<delta) delta=x;        
        }while (i!=1);
        i=n+2;
        do
        {
            j=i;i=labs(last[j]);
            if (last[j]>=0) f[i][j]+=delta;
            else f[j][i]-=delta;
        }while (i!=1);
    }
    long sum=0;
    for (i=2;i<=n+1;i++) if (f[1][i]>0) sum+=f[1][i];
    //  sum������� 
}

int main()
{
    init();  
    maxflow();
    return 0;
}
