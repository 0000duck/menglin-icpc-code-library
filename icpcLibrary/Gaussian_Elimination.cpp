/*


  Name: 高斯消元法解线性方程组，实数型


  Copyright: LogicalMars Library


  Author: Logical Mars


  Date: 12-10-08 14:38


*/


#include <stdio.h>


#include <string.h>


FILE *fin = fopen ( "gauss.in", "r" ), *fout = fopen ( "gauss.out", "w" );


const double zero = 1e-12;


int n;


double a[100][100];//系数表


double b[100];//常数表


double x[100];//答案表


void swap ( double &i, double &j )


{
    double temp = i;
    i = j;
    j = temp;
}


void swapline ( long i, long j )


{
    long k;
    for ( k = 1; k <= n; k++ ) swap ( a[i][k], a[j][k] );
    swap ( b[i], b[j] );
}


int main()


{
    fscanf ( fin, "%ld", &n ); //n元一次方程组
    long i, j;
    for ( i = 1; i <= n; i++ )
    {
        for ( j = 1; j <= n; j++ ) fscanf ( fin, "%lf", &a[i][j] );
        fscanf ( fin, "%lf", &b[i] );
    }
    long k;
    for ( k = 1; k <= n; k++ )
    {
        double max = 0;
        long l = k;
        for ( i = k; i <= n; i++ ) if ( a[i][k] > max )
            {
                max = a[i][k];
                l = i;
            }
        if ( max - zero < 0 ) continue;
        swapline ( k, l );
        for ( i = k + 1; i <= n; i++ )
        {
            double m = a[i][k] / a[k][k];
            for ( j = k; j <= n; j++ ) a[i][j] -= m * a[k][j];
            b[i] -= m * b[k];
        }
    }
    for ( i = n; i >= 1; i-- )
    {
        if ( a[i][i] - zero < 0 && b[i] - zero > 0 )
        {
            fprintf ( fout, "No Answer\n" );
            return 0;
        }
        else if ( a[i][i] - zero < 0 && b[i] - zero < 0 )
        {
            x[i] = 0;
        }
        else
        {
            double sum = b[i];
            for ( j = i + 1; j <= n; j++ ) sum -= x[j] * a[i][j];
            x[i] = sum / a[i][i];
        }
    }
    for ( i = 1; i <= n; i++ )
    {
        fprintf ( fout, "X[%ld]=%lf\n", i, x[i] );
    }
    return 0;
}

