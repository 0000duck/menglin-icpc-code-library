/*
二分图匹配，匈牙利算法，两边的顶点都是从0开始编号的
1.貌似二分图匹配多出现在棋盘上，行列各为一边
2.有些题目事实上并不是匹配的题目，而是最小点覆盖的题目，只是可以证明该图是二分图，
而又由定理，二分图的最大匹配数目等于最小点覆盖数目，所以转变成了二分匹配问题

最小点覆盖：即求最少的点使得每条边都至少和其中的一个点相关联，很显然直接取最大匹
配的一段节点即可。

二分图判定定理：当且仅当无向图的每一个回路的次数均为偶数时，才是一个偶图。如果无回
路，相当于任一回路的次数为0，0视为偶数。

在一个有向图中，路径覆盖就是在图中找一些路径，使之覆盖了图中的所有顶点，且任何一个
顶点有且只有一条路径与之关联；（如果把这些路径中的每条路径从它的起始点走到它的终点，
那么恰好可以经过图中的每个顶点一次且仅一次）；如果不考虑图中存在回路，那么每条路径就
是一个弱连通子集
最小路径覆盖就是找出最小的路径条数，使之成为图的一个路径覆盖．

路径覆盖与二分图匹配的关系： 最小路径覆盖＝｜Ｐ｜－最大匹配数；
其中最大匹配数的求法是把Ｐ中的每个顶点pi分成两个顶点pi'与pi''，
如果在p中存在一条pi到pj的边，那么在二分图Ｐ＇中就有一条连接pi'与pj''的边；

记得memset map
*/
#include <stdio.h>
#include <memory.h>
#define null 0
const int size = 510;

int maxmatch( int n, int m, bool w[][size], int *p)//if p!=0 ,p returns a set of match
{

        int p_n[size];
        int p_m[size];

        bool sign[size];
        int q[size],from[size],s,t;

        int i,j,link,now,h;

        memset( p_n, -1, sizeof(int)*n );
        memset( p_m, -1, sizeof(int)*m );

        for(i=0;i<n;i++)
        if(p_n[i]==-1)
        {
                memset( sign, 0, sizeof(bool)*m );
                
                s=1;link=-1;
                from[0]=-1;

                q[0]=size-1;
                p_m[size-1]=i;

                for(t=0;t<s;t++)
                {
                   now=q[t];
                   for(j=0;j<m;j++)
                   {
                           if( w[p_m[now]][j] != null && sign[j]==0 )
                           {
                                        sign[j]=1;
                                        q[s]=j;
                                        from[s++]=t;

                                        if(p_m[j]==-1)
                                        {
                                                link=s-1;
                                                break;
                                        }
                           }
                   }
                   if(j<m)break;
                }

                if(t<s)
                {
                         while(from[link]!=-1)
                         {
                                        h=from[link];
                                        p_m[q[link]]=p_m[q[h]];
                                        p_n[p_m[q[h]]]=q[link];
                                        link=h;
                         }
                }

                //无完备匹配
                //else return 0;
        }
        int an;

        for(i=0,an=0;i<n;i++)
        {
                if(p)p[i]=p_n[i];
                if(p_n[i]>=0)an++;
        }
        return an;
}

bool map[size][size];

int main() {
        int n, k, i, a, b;
        scanf( "%d%d", &n, &k );
        for( i=0; i<k; i++ ) {
                scanf( "%d%d", &a, &b );
                a--, b--;
                map[a][b] = 1;        //只要加一次就行了，从0开始
        }

        printf( "%d\n", maxmatch( n, n, map, 0 ) );
        return 0;
}
