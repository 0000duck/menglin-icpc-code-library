/*


  Name: 矩形切割


  Copyright: LogicalMars Library


  Author: LogicalMars


  Date: 13-10-08 13:53


  Description:


*/


#include <stdio.h>


#include <string.h>


struct recttype


{


    int x1, x2, y1, y2;


} rect[10000];


FILE *fin = fopen ( "war.in", "r" ), *fout = fopen ( "war.out", "w" );


long n, m;


long top;                               //矩形数目


void add ( int x1, int y1, int x2, int y2 )


{
    top++;
    rect[top].x1 = x1;
    rect[top].y1 = y1;
    rect[top].x2 = x2;
    rect[top].y2 = y2;
}


int cross ( int x1, int x2, int x3, int x4 ) //是否相交


{
    if ( x2 <= x3 || x4 <= x1 ) return 0;
    return 1;
}


int min ( int a, int b )


{
    if ( a < b ) return a;
    else return b;
}


int max ( int a, int b )


{
    if ( a < b ) return b;
    else return a;
}


void cut ( int x1, int y1, int x2, int y2,


           int x3, int y3, int x4, int y4, int direction ) //用后一个矩形来切割前一个


{
    int k1, k2;
    if ( direction == 1 ) //x way cut
    {
        k1 = max ( x1, x3 );
        k2 = min ( x2, x4 );
        if ( k1 > x1 ) add ( x1, y1, k1, y2 );
        if ( k2 < x2 ) add ( k2, y1, x2, y2 );
        cut ( k1, y1, k2, y2, x3, y3, x4, y4, 2 );
    }
    else if ( direction == 2 )
    {
        k1 = max ( y1, y3 );
        k2 = min ( y2, y4 );
        if ( k1 > y1 ) add ( x1, y1, x2, k1 );
        if ( k2 < y2 ) add ( x1, k2, x2, y2 );
    }
}


int main()


{
    top = 0;
    memset ( rect, 0, sizeof ( rect ) );
    long i;
    for ( i = 1; i <= m; i++ )
    {
        //---------------------
        //读入矩形
        //rect[0].x1, rect[0].y1, rect[0].x2, rect[0].y2
        //---------------------
        long j;
        long top1 = top;
        j = 1;
        while ( j <= top1 )
        {
            if ( cross ( rect[j].x1, rect[j].x2, rect[0].x1, rect[0].x2 ) &&
                    cross ( rect[j].y1, rect[j].y2, rect[0].y1, rect[0].y2 ) )
            {
                cut ( rect[j].x1, rect[j].y1, rect[j].x2, rect[j].y2, rect[0].x1, rect[0].y1, rect[0].x2, rect[0].y2, 1 );
                rect[j] = rect[top1];
                rect[top1] = rect[top];
                top1--;
                top--;
                j--;
            }
            j++;
        }
        add ( rect[0].x1, rect[0].y1, rect[0].x2, rect[0].y2 );
    }
    fclose ( fin );
    fclose ( fout );
    return 0;
}




