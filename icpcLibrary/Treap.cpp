/*


  Name: Treap


  Copyright: LogicalMars Library


  Author: LogicalMars


  Date: 12-10-08 15:20


  Description:


	堆类型：小根堆


        rotatewithleft();


        rotatewithright();


        insert(t,root);		插入t


        del(t,root);		删除t


        find();			返回第X大的数字


	go();			遍历树


*/


#include <stdio.h>


#include <string.h>


#include <math.h>


#include <stdlib.h>


#include <time.h>


const long maxn = 100010;


struct treap


{


    long x, p, left, right, chong, count;


} d[maxn];


long root, top;


void init()


{
    top = 0;
    root = 0;
    memset ( d, 0, sizeof ( d ) );
    srand ( time ( 0 ) );
}


long rotatewithleft ( long p )


{
    long p1 = d[p].left;
    d[p].left = d[p1].right;
    d[p1].right = p;
    d[p].count = d[d[p].left].count + d[d[p].right].count + d[p].chong;
    d[p1].count = d[d[p1].left].count + d[d[p1].right].count + d[p1].chong;
    return p1;
}


long rotatewithright ( long p )


{
    long p1 = d[p].right;
    d[p].right = d[p1].left;
    d[p1].left = p;
    d[p].count = d[d[p].left].count + d[d[p].right].count + d[p].chong;
    d[p1].count = d[d[p1].left].count + d[d[p1].right].count + d[p1].chong;
    return p1;
}


void insert ( long x, long &p )


{
    if ( p == 0 )
    {
        top++;
        p = top;
        d[p].x = x;
        d[p].p = rand();
        d[p].chong = 1;
        d[p].count = 1;
        d[p].left = d[p].right = 0;
    }
    else
    {
        if ( x < d[p].x )
        {
            insert ( x, d[p].left );
            if ( d[d[p].left].p < d[p].p ) p = rotatewithleft ( p );
        }
        else if ( x > d[p].x )
        {
            insert ( x, d[p].right );
            if ( d[d[p].right].p < d[p].p ) p = rotatewithright ( p );
        }
        else d[p].chong++;
        d[p].count = d[d[p].left].count + d[d[p].right].count + d[p].chong;
    }
}


void del ( long x, long &p )


{
    if ( p == 0 ) return;
    if ( x < d[p].x ) del ( x, d[p].left );
    else if ( x > d[p].x ) del ( x, d[p].right );
    else
    {
        if ( d[p].left == 0 && d[p].right == 0 )
        {
            if ( d[p].chong > 1 ) d[p].chong--;
            else p = 0;
        }
        else if ( d[p].left == 0 )
        {
            p = rotatewithright ( p );
            del ( x, p );
        }
        else if ( d[p].right == 0 )
        {
            p = rotatewithleft ( p );
            del ( x, p );
        }
        else if ( d[d[p].left].p < d[d[p].right].p )
        {
            p = rotatewithleft ( p );
            del ( x, p );
        }
        else
        {
            p = rotatewithright ( p );
            del ( x, p );
        }
    }
    if ( p == 0 ) return;
    d[p].count = d[d[p].left].count + d[d[p].right].count + d[p].chong;
}


long find ( long x, long p )


{
    while ( 1 )
    {
        if ( x <= d[d[p].left].count ) p = d[p].left;
        else if ( x <= d[d[p].left].count + d[p].chong ) return d[p].x;
        else
        {
            x -= d[d[p].left].count + d[p].chong;
            p = d[p].right;
        }
    }
}


void go ( long p )


{
    if ( d[p].left != 0 ) go ( d[p].left );
    int i;
    for ( i = 1; i <= d[p].chong; i++ ) printf ( "%ld ", d[p].x );
    if ( d[p].right != 0 ) go ( d[p].right );
}

