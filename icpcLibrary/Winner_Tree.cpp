#include <stdio.h>


#include <iostream>


using namespace std;





//NOJ 区间最值 赢家树


#define MAX 9999999


#define NMAX 12000


long shuru[NMAX];


long a[NMAX * 2];





void create ( long num )


{
    //构造一个完全二叉树
    long i;
    //a[num],a[num+1]...a[num*2-1]是原数
    for ( i = 0; i < num; i++ ) a[num + i] = shuru[i];
    for ( i = num - 1; i >= 1; i-- )
    {
        //构造父节点
        if ( a[2 * i] > a[2 * i + 1] ) a[i] = a[2 * i + 1];
        else a[i] = a[2 * i];
    }
}





long find ( long num, long left, long right )


{
    long min = MAX;
    left = num + left - 1;
    right = num + right - 1;
    if ( min > a[left] ) min = a[left];
    if ( min > a[right] ) min = a[right];
    while ( left <= right && left >= 1 && right >= 1 )
    {
        //注意循环条件，不加left>=1&&right>=1会出现死循环
        if ( min > a[left] ) min = a[left];
        if ( min > a[right] ) min = a[right];
        //从树底开始，一直往上求
        left = ( left + 1 ) / 2;
        right = ( right - 1 ) / 2;
    }
    return min;
}





int main()


{
    long num, i, pnum, ll, rr;
    scanf ( "%ld", &num );
    for ( i = 0; i < num; i++ )
    {
        scanf ( "%ld", &shuru[i] );
    }
    create ( num );
    scanf ( "%ld", &pnum );
    for ( i = 0; i < pnum; i++ )
    {
        scanf ( "%ld%ld", &ll, &rr );
        printf ( "%ld\n", find ( num, ll, rr ) );
    }
    return 0;
}