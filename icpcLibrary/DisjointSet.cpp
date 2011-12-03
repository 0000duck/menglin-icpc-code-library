/*
  Name: Disjoint Net
  Copyright: LogicalMars Library
  Author: LogicalMars
  Date: 12-10-08 19:04
  Description: father[i]表示i的父节点，初始时father[i]=i; 
*/
int find_father(int x)//父子关系仅为存在时的简单程序处理 
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

long fath(long p)//父子关系多样时，ch[i] 为 i与父节点的关系 
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

