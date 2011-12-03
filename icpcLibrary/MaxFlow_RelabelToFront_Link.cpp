#include <algorithm>
#include <climits>
#include <cstring>
using namespace std;
const int maxn=100;
//Add a reversal edge with capacity 0 for each edge in a directed graph.
struct edge{int v,c,next;};
void push(int u,edge &e,int x[],int f[][maxn])
{
	int c=min(x[u],e.c-f[u][e.v]);
	f[u][e.v]+=c;
	f[e.v][u]-=c;
	x[u]-=c;
	x[e.v]+=c;
}
void relabel(int u,int g[],edge e[],int h[],int f[][maxn])
{
	int z=h[u];
	for(int i=g[u];i!=-1;i=e[i].next)
		if(e[i].c-f[u][e[i].v]>0&&z>h[e[i].v]) z=h[e[i].v];
	h[u]=z+1;
}
int RelabelToFront(int g[],edge e[],int n,int src,int dst,int f[][maxn])
{
	int l[maxn],h[maxn]={0},x[maxn]={0},q[maxn];
	memset(f,0,sizeof(*f)*n);
	memcpy(q,g,sizeof(q));
	h[src]=n;x[src]=INT_MAX;
	for(int i=0,j=0;i<n;i++) if(i!=src&&i!=dst) l[j++]=i;
	for(int i=g[src];i!=-1;i=e[i].next) push(src,e[i],x,f);
	for(int p=0;p<n-2;p++)
	{
		int u=l[p],k=h[u];
		while(x[u]>0)
		{
			if(q[u]==-1) {relabel(u,g,e,h,f);q[u]=g[u];}
			else
			{
				edge &v=e[q[u]];
				if(v.c-f[u][v.v]>0&&h[u]>h[v.v]) push(u,v,x,f);
				else q[u]=v.next;
			}
		}
		if(h[u]>k)
		{
			memmove(l+1,l,sizeof(*l)*p);
			l[0]=u;p=0;
		}
	}
	return x[dst];
}
