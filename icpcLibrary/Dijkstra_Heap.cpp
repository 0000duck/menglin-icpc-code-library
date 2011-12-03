/*
  Name: Dijkstra Heap版 
  Copyright: LogicalMars    
  Author: LogicalMars  
  Date: 12-10-08 12:52
  Description: 邻接表数据结构 
*/
using namespace std;
#include <fstream>
#include <string.h>
ifstream fin("butter.in");
ofstream fout("butter.out");
const long maxnum=0x7fffffff/4;
const long maxn=810;  //最大顶点数 
int n;                //顶点数目 
struct nodetype{
                int v;//表中顶点 
                int l;//距离 
                nodetype *next;
               };
nodetype *map[maxn];//邻接表 
long q[maxn];
long qpos[maxn];
long dis[maxn];
long qtot;          //Heap
void swap(int i,int j)
 {
  long k=q[i];
  q[i]=q[j];
  q[j]=k;
  qpos[q[i]]=i;
  qpos[q[j]]=j;
 }
void up(int i)
 {
  int j=i/2;				//j一定是i的父亲
  while (dis[q[j]]>dis[q[i]] && j>=1)
   {
    swap(j,i);
    i=j;j=i/2;
   }
 }
void down(int i)
 {
  int j;
  do
   {
    j=i;
    long min=maxnum;//相当的关键，min存的是儿子中最小的一个
    if (i*2+1<=qtot && dis[q[i*2+1]]<min) {min=dis[q[i*2+1]];i=i*2+1;}
    if (j*2<=qtot && dis[q[j*2]]<min) {min=dis[q[j*2]];i=j*2;}
    if (min<dis[q[j]]) swap(i,j);
   }while (i!=j);
 }

void relax(int i,int j,int w)
 {
  if (w>=dis[j]) return;
  dis[j]=w;
  up(qpos[j]);
 }
long dijkstra(int s)
 {
  int i,j;
  for (i=1;i<=n;i++)
   {
    dis[i]=maxnum;
    q[i]=i;
    qpos[i]=i;
   }
  swap(s,1);
  qtot=n;
  dis[s]=0;
  
  while (qtot>1)
   {
    i=q[1];
    swap(1,qtot);//保证qpos也改了，所以q[1]=q[qtot]是错的
    qtot--;

    down(1);
    
    nodetype *p=map[i];
    while (p)
     {
      if (qpos[p->v]<=qtot) relax(i,p->v,dis[i]+p->l);
      p=p->next;
     }
   }
   
  //dis已经产生 
  long sum=0;
  for (i=1;i<=n;i++)
   {
    if (dis[i]==maxnum) continue;
    if (dis[i]>0) sum+=dis[i]; 
   }
  return sum;
 }
int main()
 {
  int p,m;
  fin>>n>>m;            //m是边数 
  int i; 
  memset(map,0,sizeof(map));
  for (i=1;i<=m;i++)
   {
    int a,b,l;
    fin>>a>>b>>l;
    
    nodetype *p=new nodetype;
    p->next=map[a];
    p->v=b;
    p->l=l;
    map[a]=p;

    nodetype *qq=new nodetype;
    qq->next = map[b];
    qq->v = a;
    qq->l = l;
    map[b]=qq;
   }  
  return 0;
 }
