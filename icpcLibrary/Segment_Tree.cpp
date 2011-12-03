/*
  Name:  Segment Tree
  Copyright: LogicalMars Library
  Author: LogicalMars
  Date: 15-10-08 13:22
  Description: �߶��������룬ɾ��������ͳ��
*/
#include <stdio.h>
#include <string.h>
const long maxn=20000;
struct treetype
{
    long a,b;       //���ҷ�Χ		!!ע���ǵ�
    long left,right;//���Ҷ���
    long cover;     //����
    long bj;        //ɾ�����,-1��ʾ�ѱ�ɾ��
}tree[maxn];
long tot;           //treeָ��
long Ans;
void maketree(long a,long b)
{
    tot++;
    int now=tot;
    tree[now].a=a;
    tree[now].b=b;
    if (a+1<b)
    {
        tree[now].left=tot+1;
        maketree(a,(a+b)/2);
        tree[now].right=tot+1;
        maketree((a+b)/2,b);
    }
}
void init()
{
    memset(tree,0,sizeof(tree));
    tot=0;
    Ans=0;
    //maketree( , );
}
void clean(long num)//���±�ǵĹ���
{
    tree[num].cover=0;
    tree[num].bj=0;
    tree[tree[num].left].bj=-1;
    tree[tree[num].right].bj=-1;
}
void insert(long num,long c,long d);//�����߶�
{
    long mid;
    if (tree[num].bj==-1) clean(num);
    if (tree[num].cover==1) return;
    if (c<=tree[num].a && d>=tree[num].b)
    {
        tree[num].cover=1;
    }
    else
    {
        mid=(tree[num].a + tree[num].b)/2;
        if (c<mid) insert(tree[num].left,c,d);
        if (d>mid) insert(tree[num].right,c,d);
    }
}
void del(long num,long c,long d)//ɾ���߶�
{
    long mid;
    if (tree[num].b==-1) return;
    if (c<=tree[num].a && d>=tree[num].b)
    {
        tree[num].cover=0;
        tree[tree[num].left].bj=-1;
        tree[tree[num].right].bj=-1;
        return;
    }
    if (tree[num].cover==1)
    {
        tree[num].cover=0;
        tree[tree[num].left].bj=-1;
        tree[tree[num].right].bj=-1;
        if (tree[num].a<c) insert(num,tree[num].a,c);
        if (d<tree[num].b) insert(num,d,tree[num].b);
    }
    else
    {
        mid=(tree[num].a + tree[num])/2;
        if (c<mid) del(tree[num].left,c,d);
        if (d>mid) del(tree[num].right,c,d);
    }
}
void calc(long num)//ͳ�Ʊ����ǵĳ��ȣ��ӵ�Ans�У�Ҫ��Ans֮ǰҪ����
{
    if (num==0) return;
    if (tree[num].bj==-1) return;
    if (tree[num].cover==1)
    {
        Ans+=tree[num].b-tree[num].a;
        return;
    }
    calc(tree[num].left);
    calc(tree[num].right);
}
