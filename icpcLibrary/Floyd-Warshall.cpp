
/*==========================================

              每对节点间最短路径
                Floyd-Warshall 算法

    D[i,j]表示从i到j的最短距离；
    P[i,j]表示从i到j的最短路径上j 的父节点

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