
/*==========================================

              ÿ�Խڵ�����·��
                Floyd-Warshall �㷨

    D[i,j]��ʾ��i��j����̾��룻
    P[i,j]��ʾ��i��j�����·����j �ĸ��ڵ�

===========================================*/

void Floyd_Washall(Graph G,int n,Graph D,Graph P)
{
    int i,j,k;
    for (i=0;i<n;i++)
        for (j=0;j<n;j++)
            {   D[i][j]=G[i][j];
                P[i][j]=i;       }
    for (i=0;i<n;i++) {   D[i][i]=0;P[i][i]=0; }
    for (k=0;k<n;k++)
        for (i=0;i<n;i++)
            for (j=0;j<n;j++)
                if (D[i][j]>D[i][k]+D[k][j])
                {   D[i][j]=D[i][k]+D[k][j];
                    P[i][j]=P[k][j];
                    }
}