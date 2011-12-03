/*
  Name: ����˷������Ʒ��� 
  Copyright: LogicalMars Library
  Author: LogicalMars
  Date: 13-10-08 22:59
  Description: An = Sum(Xi * A(n-i)),i=1,2,...,k,�������A =��A1,A2,...,Ak),
               ���� Matrix, ���������������Ĵ�СΪk*k�����ĵ�k��Ϊx1��xk��ע��Ϊ���򣬼����ƹ�ϵ�е�ϵ���� 
               ��i(1<=i<=k)���г���i+1��Ԫ��Ϊ1�⣬����Ԫ�ؾ�Ϊ0��
               
               ������ An = An-1 + 2 * An-2, A1=1,A0=0;
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
        //                                          ��ʼ�� 
        k=2;
        memset(Matrix,0,sizeof(Matrix));
        Matrix[1][2]=2;Matrix[2][1]=1;Matrix[2][2]=1;//����ϵ������ 
        A[1]=0;A[2]=1;          //AΪ��ֵ����    
        
        memset(m,0,sizeof(m)); //mΪk�׵ĵ�λ���� 
        m[1][1]=1; m[2][2]=1;
        //--------------------------------------------------- 
        
        int nn=n-1;              //���ַ�����An                   
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
