/*
  Name: Disjoint Net
  Copyright: LogicalMars Library
  Author: LogicalMars
  Date: 12-10-08 19:04
  Description: father[i]��ʾi�ĸ��ڵ㣬��ʼʱfather[i]=i; 
*/
int find_father(int x)//���ӹ�ϵ��Ϊ����ʱ�ļ򵥳����� 
{
    int i,f,next,j;
    i=x;    
    while (father[i]!=i) i=father[i];
    f=i;
    
    i=x;
    while (i!=f)
    {
        next=father[i];
        father[i]=f;        
        i=next;
    }    
    
    return f;
}

long fath(long p)//���ӹ�ϵ����ʱ��ch[i] Ϊ i�븸�ڵ�Ĺ�ϵ 
 {
  if (fa[p]==p) return p;
  if (fa[fa[p]]==fa[p]) return fa[p];
  long k=fath(fa[p]);
  ch[p]=mod3(ch[fa[p]]+ch[p]);
  fa[p]=k;
  return k;
 }
 
void add(long x,long y)
{
    long px=find_father(x);
    long py=find_father(y);
    if (px!=py)
    {
        father[px]=py;
        //ch[i]=
    }
}

