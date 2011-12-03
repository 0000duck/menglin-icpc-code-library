/*
  Name: Dijkstra Heap�� 
  Copyright: LogicalMars    
  Author: LogicalMars  
  Date: 12-10-08 12:52
  Description: �ڽӱ����ݽṹ 
*/
using namespace std;
#include <fstream>
#include <string.h>
ifstream fin("butter.in");
ofstream fout("butter.out");
const long maxnum=0x7fffffff/4;
const long maxn=810;  //��󶥵��� 
int n;                //������Ŀ 
struct nodetype{
                int v;//���ж��� 
                int l;//���� 
                nodetype *next;
               };
nodetype *map[maxn];//�ڽӱ� 
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
  int j=i/2;				//jһ����i�ĸ���
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
    long min=maxnum;//�൱�Ĺؼ���min����Ƕ�������С��һ��
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
    swap(1,qtot);//��֤qposҲ���ˣ�����q[1]=q[qtot]�Ǵ��
    qtot--;

    down(1);
    
    nodetype *p=map[i];
    while (p)
     {
      if (qpos[p->v]<=qtot) relax(i,p->v,dis[i]+p->l);
      p=p->next;
     }
   }
   
  //dis�Ѿ����� 
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
  fin>>n>>m;            //m�Ǳ��� 
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
