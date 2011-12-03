/*
  Name: 矩阵乘法求解递推方程 
  Copyright: LogicalMars Library
  Author: LogicalMars
  Date: 13-10-08 22:59
  Description: An = Sum(Xi * A(n-i)),i=1,2,...,k,构造矩阵A =（A1,A2,...,Ak),
               矩阵 Matrix, 有如下特征：它的大小为k*k；它的第k列为x1至xk，注意为倒序，即递推关系中的系数； 
               第i(1<=i<=k)列中除第i+1行元素为1外，其余元素均为0。
               
               本程序 An = An-1 + 2 * An-2, A1=1,A0=0;
*/
#include <stdio.h>
#include <string.h>
long Matrix[50][50],m[50][50];
long A[50];
int k,n;
int main()
{
    freopen("matrix.in","r",stdin);
    freopen("matrix.out","w",stdout);
    for (n=1;n<=30;n++)
    {
        //                                          初始化 
        k=2;
        memset(Matrix,0,sizeof(Matrix));
        Matrix[1][2]=2;Matrix[2][1]=1;Matrix[2][2]=1;//构造系数矩阵 
        A[1]=0;A[2]=1;          //A为初值矩阵    
        
        memset(m,0,sizeof(m)); //m为k阶的单位矩阵 
        m[1][1]=1; m[2][2]=1;
        //--------------------------------------------------- 
        
        int nn=n-1;              //二分法计算An                   
        while (nn)
        {   
            int i,j,t;
            int m3[50][50];
            if (nn%2==1) 
            {
                memset(m3,0,sizeof(m3));
                for (i=1;i<=k;i++)
                {
                    for (j=1;j<=k;j++)
                    {
                        for (t=1;t<=k;t++) m3[i][j]+=m[i][t] * Matrix[t][j];
                    }
                }
                memcpy(m,m3,sizeof(m3));
            } 
            nn/=2;        
            memset(m3,0,sizeof(m3));
            for (i=1;i<=k;i++)
            {
                for (j=1;j<=k;j++)
                {
                    for (t=1;t<=k;t++) m3[i][j]+=Matrix[i][t] * Matrix[t][j];
                }
            }
            memcpy(Matrix,m3,sizeof(m3));                
        }
        printf(" n=%ld ,%lld\n",n,A[1]*m[1][2]+A[2]*m[2][2]);
    }
    return 0;
}
