/*


  Name:  Segment Tree


  Copyright: LogicalMars Library


  Author: LogicalMars


  Date: 15-10-08 13:22


  Description: 线段数，插入，删除，查找统计


*/


#include <stdio.h>


#include <string.h>


const long maxn = 20000;


struct treetype


{


    long a, b;      //左右范围		!!注意是点


    long left, right; //左右儿子


    long cover;     //覆盖


    long bj;        //删除标记,-1表示已被删除


} tree[maxn];


long tot;           //tree指针


long Ans;


void maketree ( long a, long b )


{
    tot++;
    int now = tot;
    tree[now].a = a;
    tree[now].b = b;
    if ( a + 1 < b )
    {
        tree[now].left = tot + 1;
        maketree ( a, ( a + b ) / 2 );
        tree[now].right = tot + 1;
        maketree ( ( a + b ) / 2, b );
    }
}


void init()


{
    memset ( tree, 0, sizeof ( tree ) );
    tot = 0;
    Ans = 0;
    //maketree( , );
}


void clean ( long num ) //更新标记的过程


{
    tree[num].cover = 0;
    tree[num].bj = 0;
    tree[tree[num].left].bj = -1;
    tree[tree[num].right].bj = -1;
}


void insert ( long num, long c, long d ); //插入线段


{
    long mid;
    if ( tree[num].bj == -1 ) clean ( num );
    if ( tree[num].cover == 1 ) return;
    if ( c <= tree[num].a && d >= tree[num].b )
    {
        tree[num].cover = 1;
    }
    else
    {
        mid = ( tree[num].a + tree[num].b ) / 2;
        if ( c < mid ) insert ( tree[num].left, c, d );
        if ( d > mid ) insert ( tree[num].right, c, d );
    }
}


void del ( long num, long c, long d ) //删除线段


{
    long mid;
    if ( tree[num].b == -1 ) return;
    if ( c <= tree[num].a && d >= tree[num].b )
    {
        tree[num].cover = 0;
        tree[tree[num].left].bj = -1;
        tree[tree[num].right].bj = -1;
        return;
    }
    if ( tree[num].cover == 1 )
    {
        tree[num].cover = 0;
        tree[tree[num].left].bj = -1;
        tree[tree[num].right].bj = -1;
        if ( tree[num].a < c ) insert ( num, tree[num].a, c );
        if ( d < tree[num].b ) insert ( num, d, tree[num].b );
    }
    else
    {
        mid = ( tree[num].a + tree[num] ) / 2;
        if ( c < mid ) del ( tree[num].left, c, d );
        if ( d > mid ) del ( tree[num].right, c, d );
    }
}


void calc ( long num ) //统计被覆盖的长度，加到Ans中，要求Ans之前要清零


{
    if ( num == 0 ) return;
    if ( tree[num].bj == -1 ) return;
    if ( tree[num].cover == 1 )
    {
        Ans += tree[num].b - tree[num].a;
        return;
    }
    calc ( tree[num].left );
    calc ( tree[num].right );
}

