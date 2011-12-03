/*


  Name: 最小费用最大流


  Copyright: LogicalMars Library


  Author: LogicalMars


  Date: 17-10-08 12:04


  Description:


*/


#include <stdio.h>


#include <string.h>


FILE *fin = fopen ( "napkin.in", "r" ), *fout = fopen ( "napkin.out", "w" );


const long maxlong = 0x7fffffff / 2;


const long maxn = 2010;


long f[maxn][maxn], map[maxn][maxn], fee[maxn][maxn], last[maxn], best[maxn];


//      f存储流量， map存储流量上限，fee存储费用


long n, nd[maxn], fnew, fa, fb, da, db;


long to;//汇


struct point


{


    long k;


    point *next, *other;


}*link[maxn];


long labs ( long x )


{
    if ( x < 0 ) return -x;
    return x;
}


void add ( long x, long y )


{
    point *p = new point;
    p->k = y;
    p->next = p->other = NULL;
    p->next = link[x]->next;
    link[x]->next = p;
    point *q = new point;
    q->k = x;
    q->next = q->other = NULL;
    q->next = link[y]->other;
    link[y]->other = q;
}


void adde ( long x, long y, long cap, long fe )


{
    add ( x, y );
    map[x][y] = cap;
    fee[x][y] = fe;
}


void init()


{
    long i, j;
    memset ( fee, 0, sizeof ( fee ) );
    memset ( map, 0, sizeof ( map ) );
    //读入图
    to = ??
         //
         for ( i = 1; i <= to; i++ )
    {
        link[i] = new point;
        link[i]->k = 0;
        link[i]->next = link[i]->other = NULL;
    }
    //构图
}


long d[maxn];//采用取队尾的方法删除


short visit[maxn];


void costflow() //计算从1到to的最小费用最大流


{
    memset ( f, 0, sizeof ( f ) );
    long i, j;
    long cost = 0;
    long h, t;
    while ( 1 )
    {
        memset ( last, 0, sizeof ( last ) );
        memset ( d, 0, sizeof ( d ) );
        memset ( visit, 0, sizeof ( visit ) );
        h = t = 1;
        for ( i = 1; i <= to; i++ ) best[i] = maxlong;
        best[1] = 0;
        last[1] = 1;
        d[1] = 1;
        visit[1] = 1;
        do
        {
            i = d[h];
            point *p = link[i]->next;
            while ( p )
            {
                j = p->k;
                if ( f[i][j] < map[i][j] && best[i] + fee[i][j] < best[j] )
                {
                    best[j] = best[i] + fee[i][j];
                    last[j] = i;
                    if ( !visit[j] )
                    {
                        t++;
                        d[t] = j;
                        visit[j] = 1;
                    }
                }
                p = p->next;
            }
            p = link[i]->other;
            while ( p )
            {
                j = p->k;
                if ( f[j][i] > 0 && best[i] - fee[j][i] < best[j] )
                {
                    best[j] = best[i] - fee[j][i];
                    last[j] = -i;
                    if ( !visit[j] )
                    {
                        t++;
                        d[t] = j;
                        visit[j] = 1;
                    }
                }
                p = p->next;
            }
            visit[i] = 0;
            d[h] = d[t];
            t--;
        }
        while ( h <= t );
        if ( best[to] == maxlong ) break;
        long delta = maxlong;
        i = to;
        do
        {
            j = i;
            i = labs ( last[i] );
            long xx;
            if ( last[j] > 0 ) xx = map[i][j] - f[i][j];
            else xx = f[j][i];
            if ( xx < delta ) delta = xx;
        }
        while ( i != 1 );
        i = to;
        do
        {
            j = i;
            i = labs ( last[i] );
            if ( last[j] > 0 ) f[i][j] += delta;
            else f[j][i] -= delta;
        }
        while ( i != 1 );
        cost += delta * best[to];
    }
    fprintf ( fout, "%ld", cost );
}

