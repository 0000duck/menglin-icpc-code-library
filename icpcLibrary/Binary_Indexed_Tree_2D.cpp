/*


  Name: 树状数组二维


  Copyright: LogicalMars Library


  Author: LogicalMars


  Date: 16-10-08 22:23


  Description: 快速求(1,1)到(x,y)处的矩阵的和


*/


#include <string.h>


#include <stdio.h>


long lowbit ( long x )


{
    return x & ( x ^ ( x - 1 ) );
}


void insert ( long x, long y, long a ) //对(x,y)加上a


{
    long i, j;
    i = x;
    j = y;
    while ( i <= maxn )
    {
        j = y;
        while ( j <= maxn )
        {
            c[i][j] += a;
            j += lowbit ( j );
        }
        i += lowbit ( i );
    }
}


long sum ( long x, long y )         //求和（1，1）到（x，y)


{
    long re = 0;
    long i = x, j = y;
    while ( i > 0 )
    {
        j = y;
        while ( j > 0 )
        {
            re += c[i][j];
            j -= lowbit ( j );
        }
        i -= lowbit ( i );
    }
    return re;
}

