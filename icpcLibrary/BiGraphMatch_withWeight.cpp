/*
二分图最大权匹配
PKU2195
*/
#include <iostream>
#include <algorithm>
#include <memory.h>
#include <stdio.h>
using namespace std;
#define N 200
#define MAX 0
int dis[N][N];//存储边权，边权等于MAX表示不通
int homematch[N],personmatch[N];//左边person集合，右边home集合
bool personset[N],homeset[N];
int person[N],home[N];
int homex[N],homey[N];
int personx[N],persony[N];
inline bool canmatch(int p,int h)
{
	return dis[p][h]==person[p]+home[h];
}
int max(int a,int b)
{
return a>b?a:b;
}
int min(int a,int b)
{
return a<b?a:b;
}
bool findtree(int p,int n)
{
	personset[p]=true;
	int h;
	for(h=0;h<n;h++)
	{
		if(canmatch(p,h)&&!homeset[h])
		{
			homeset[h]=true;
			if(homematch[h]==-1||findtree(homematch[h],n))
			{
				homematch[h]=p;
				personmatch[p]=h;
				return true;
			}
		}
	}
	return false;
}
void relabel(int n)
{
	int p,h,mind=100000000;
	for(p=0;p<n;p++)
	{
		if(personset[p])
		{
			for(h=0;h<n;h++)
			{
				if(!homeset[h])
				{
					mind=min(mind,home[h]+person[p]-dis[p][h]);
				}
			}
		}
	}
	for(p=0;p<n;p++)
	{
		if(personset[p])
		{
			person[p]-=mind;
		}
	}
	for(h=0;h<n;h++)
	{
		if(homeset[h])
			home[h]+=mind;
	}
}
bool maxmatch(int n)
{
	memset(homematch,0xff,sizeof(int)*n);
	memset(personmatch,0xff,sizeof(int)*n);
	int p;
	for(p=0;p<n;p++)
	{

		memset(personset,false,sizeof(bool)*n);
		memset(homeset,false,sizeof(bool)*n);
		while(!findtree(p,n))
		{
			relabel(n);
			memset(personset,false,sizeof(bool)*n);
			memset(homeset,false,sizeof(bool)*n);
		}
	}
	return true;
}

int mincost(int n)
{
	int p,h,maxd;
	for(p=0;p<n;p++)
	{
		maxd=0;
		for(h=0;h<n;h++)
		{
			maxd=max(maxd,dis[p][h]);
		}
		person[p]=maxd;
		home[p]=0;
	}
	maxmatch(n);//最大权匹配
	maxd=0;
	for(p=0;p<n;p++)
	{
		maxd+=(MAX-dis[p][personmatch[p]]);
	}
	return maxd;
}
int read(int r,int c)
{
	int pn=0,hn=0;
	int i,j;
	char line[N];
	for(i=0;i<r;i++)
	{
		scanf("%s",line);
		for(j=0;j<c;j++)
		{
			if(line[j]=='H')
			{
				homex[hn]=j;
				homey[hn]=i;
				hn++;
			}
			else if(line[j]=='m')
			{
				personx[pn]=j;
				persony[pn]=i;
				pn++;
			}
		}
	}
	for(i=0;i<pn;i++)
	{
		for(j=0;j<hn;j++)
		{
			dis[i][j]=abs(personx[i]-homex[j])+abs(persony[i]-homey[j]);
			dis[i][j]=MAX-dis[i][j];
		}
	}
	return pn;
}

int main()
{
	int r,c,n;
	while(scanf("%d %d",&r,&c)!=EOF&&r>0&&c>0)
	{
		n=read(r,c);
		printf("%d\n",mincost(n));
	}
	return 0;
}
