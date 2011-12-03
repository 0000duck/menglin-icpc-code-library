/*======================================================

      ��Դ���·��

   Bellman-Ford �㷨

 ���������������������Ȩ����Ϊ��
 GΪͼ��nΪͼ�Ľڵ���Ŀ,s,t�ֱ�ΪԴ����յ�,
 success������ʾ�ú����Ƿ�ɹ���
 �������һ����Դ��ɴ��ȨΪ���Ļ�·��success=false;
 ����ֵΪs,t֮������·�����ȣ�


            !!ע�⣺
            1.�����Ŵ�0��ʼ
            2.��i,j������ʱG[i,j]=infinity

=============================================================*/

int Bellman_Ford(Graph G,int n,int s,int t,int path[],int success)
{
   int i,j,k,d[max_vertexes];
   for (i=0;i<n;i++) {d[i]=infinity;path[i]=0;}
   d[s]=0;
   for (k=1;k<n;k++)
    for (i=0;i<n;i++)
     for (j=0;j<n;j++)
       if (d[j]>d[i]+G[i][j]) {d[j]=d[i]+G[i][j];path[j]=i;}
   success=0;
   for (i=0;i<n;i++)
    for (j=0;j<n;j++)
     if (d[j]>d[i]+G[i][j]) return 0;
   success=1;
   return d[t];
 }