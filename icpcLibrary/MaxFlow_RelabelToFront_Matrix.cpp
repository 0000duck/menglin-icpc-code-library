#include <algorithm>
#include <climits>
#include <cstring>
using namespace std;
const int maxn=100;
void push(int u,int v,int g[][maxn],int x[],int f[][maxn])
{
	int c=min(x[u],g[u][v]-f[u][v]);
	f[u][v]+=c;
	f[v][u]-=c;
	x[u]-=c;
	x[v]+=c;
}
void relabel(int u,int g[][maxn],int n,int h[],int f[][maxn])
{
	int z=h[u];
	for(int i=0;i<n;i++)
		if(g[u][i]-f[u][i]>0&&z>h[i]) z=h[i];
	h[u]=z+1;
}
int RelabelToFront(int g[][maxn],int n,int src,int dst,int f[][maxn])
{
	int l[maxn],h[maxn]={0},x[maxn]={0},q[maxn]={0};
	memset(f,0,sizeof(*f)*n);
	h[src]=n;x[src]=INT_MAX;
	for(int i=0,j=0;i<n;i++)
	{
		if(i!=src&&i!=dst) l[j++]=i;
		push(src,i,g,x,f);
	}
	for(int p=0;p<n-2;p++)
	{
		int u=l[p],k=h[u];
		while(x[u]>0)
		{
			if(q[u]<n)
			{
				int v=q[u];
				if(g[u][v]-f[u][v]>0&&h[u]>h[v]) push(u,v,g,x,f);
				else q[u]++;
			}
			else
			{
				relabel(u,g,n,h,f);
				q[u]=0;
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
