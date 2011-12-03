//Belongs to Logical Mars Library
/*===============================================

                ��Դ���·��

                Dijkstra �㷨

            �������������бߵ�Ȩ�Ǹ�

            !!ע�⣺
            1.�����ͼ��Ȩ����Ǹ�
            2.�����Ŵ�0��ʼ
            3.��i,j������ʱG[i,j]=infinity

================================================*/
int Dijkstra(Graph G,int n,int s,int t, int path[])
{
    int i,j,w,minc,d[max_vertexes],mark[max_vertexes];
    for (i=0;i<n;i++) mark[i]=0;
    for (i=0;i<n;i++)
        {   d[i]=G[s][i];
            path[i]=s;	}
    mark[s]=1;path[s]=0;d[s]=0;
    for (i=1;i<n;i++)
		{   minc=infinity;
          w=0;
          for (j=0;j<n;j++)
            if ((mark[j]==0)&&(minc>=d[j])) {minc=d[j];w=j;}
          mark[w]=1;
          for (j=0;j<n;j++)
            if ((mark[j]==0)&&(G[w][j]!=infinity)&&(d[j]>d[w]+G[w][j]))
                {   d[j]=d[w]+G[w][j];
                    path[j]=w;     }
      }
    return d[t];
}
