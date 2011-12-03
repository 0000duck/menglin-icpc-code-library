/*======================================================





      单源最短路径





   Bellman-Ford 算法





 适用条件：所有情况，边权可以为负


 G为图，n为图的节点数目,s,t分别为源点和终点,


 success用来标示该函数是否成功，


 如果存在一个从源点可达的权为负的回路则success=false;


 返回值为s,t之间的最短路径长度；








            !!注意：


            1.顶点标号从0开始


            2.当i,j不相邻时G[i,j]=infinity





=============================================================*/





int Bellman_Ford ( Graph G, int n, int s, int t, int path[], int success )


{
    int i, j, k, d[max_vertexes];
    for ( i = 0; i < n; i++ )
    {
        d[i] = infinity;
        path[i] = 0;
    }
    d[s] = 0;
    for ( k = 1; k < n; k++ )
        for ( i = 0; i < n; i++ )
            for ( j = 0; j < n; j++ )
                if ( d[j] > d[i] + G[i][j] )
                {
                    d[j] = d[i] + G[i][j];
                    path[j] = i;
                }
    success = 0;
    for ( i = 0; i < n; i++ )
        for ( j = 0; j < n; j++ )
            if ( d[j] > d[i] + G[i][j] ) return 0;
    success = 1;
    return d[t];
}