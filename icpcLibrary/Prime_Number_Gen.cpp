/*







  Name: Prime_Gen







  Copyright: LogicalMars Library







  Author: LogicalMars







  Date: 12-10-08 13:55







  Description: 绛涙硶浜х敓绱犳暟







*/







#include <string.h>







#include <stdio.h>







const long maxn = 10000;







long prime[maxn];







short check[maxn + 50];







long pp;







int main()







{
    freopen ( "prime.out", "w", stdout );
    memset ( check, 0, sizeof ( check ) );
    long i = 2;
    pp = 0;
    while ( i <= maxn )
    {
        while ( check[i] ) i++;
        pp++;
        prime[pp] = i;
        long j;
        j = i * 2;
        while ( j <= maxn )
        {
            check[j] = 1;
            j += i;
        }
        i++;
    }
    for ( i = 1; i <= pp; i++ ) printf ( "%ld ", prime[i] );
    return 0;
}



















