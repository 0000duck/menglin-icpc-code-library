/*Pku 1021  Intervals
 * 差分约束系统 BellmanFord 队列优化版
 * AC
*/
#include <string.h>
#include <stdio.h>
const int maxn = 50010;//最大顶点数
const int maxnum=0x7fffffff/4;
int st,ed;
int n;                                  //顶点数目 
struct nodetype{
                int v;                  //表中顶点 
                int l;                   //距离 
                nodetype *next;
               };
nodetype *map[maxn];   //邻接表 
void add_edge(int a,int b,int l) //由a向b连一条权为l的边
{
        nodetype *p=new nodetype;
        p->next=map[a];
        p->v=b;
        p->l=l;
        map[a]=p;
}
int Q[maxn*100];
short inQ[maxn+10];
void Bellmanford()
{
        int dis[maxn];
        memset(Q,0,sizeof(Q));
        memset(inQ,0,sizeof(inQ));
        memset(dis,0,sizeof(dis));
        
        int h,t,i;
        h=0;
        for (i=st-1;i<=ed;i++)
        {
                h++;
                Q[h]=i;
                inQ[i]=1;
        }
        t=h;
        h=1;
        int count=0;
        int flag=0;
        while (h<=t)
        {
                int x=Q[h];
                inQ[x]=0;
                nodetype *p=map[x];                             // map[x]中有效的部分从map[x]就开始了
                while (p!=NULL)
                {
                        count++;  
                        if (p->l + dis[x] > dis[p->v])            //此处求最长路径
                        {
                                dis[p->v] = p->l + dis[x];
                                if (!inQ[p->v]) {t++;Q[t]=p->v;inQ[p->v]=1;}
                        }
                        p=p->next;
              }
              h++;
              if (count>m*n) {flag=1;break;}//m为边数
      }
      //if (flag) 有环
      //dis已经生成
      printf("%d\n",dis[ed]-dis[st-1]);
}                
 int main()
 {
         //freopen("1201.in","r",stdin);
         scanf("%d",&n);
         int i;
         ed=0;
         st=999999;
         memset(map,0,sizeof(map));
         for (i=1;i<=n;i++)
         {
                 int a,b,c;
                 scanf("%d%d%d",&a,&b,&c);
                 a++;
                 b++;
                 if (a<st) st=a;
                 if (b>ed) ed=b;
                 add_edge(a-1,b,c);
         }
         for (i=st;i<=ed;i++)
         {
                 add_edge(i-1,i,0);
                 add_edge(i,i-1,-1);
         }
         Bellmanford();
         return 0;
 }
