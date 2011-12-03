/*Logical Mars Codes Library
 * 
 * ���Լ��ϵͳ
 *
 *      һ��ڵ�S���Ƕ���ĳ�����еĺͣ����������������������⣬�ڵ���Ϊ������ϵ����ֳ��ִ���
 *      �ĺͣ��Ϳ��Խ�һЩ���������͵����⡣ע�����ʱ������Ӧ����dis[n] - dis[0]��
 *      �����ֵ��������<=��ͼ�����·��
 *      ����Сֵ��������>=��ͼ���·��
 */
 #include <string.h>
 #include <stdio.h>
 const int maxn = 110;//��󶥵���
 const int maxm = 110;//������
 int s[maxn];
 int edge[maxm][3];
 int es;
 int n,m;
void add_edge(int a,int b,int c) //��a��b��һ����ȨΪc�ı�
 {
         es++;
         edge[es][1]=a;
         edge[es][2]=b;
         edge[es][0]=c;
 }
 void Bellmanford()
 {
         int i,j;
         int dis[maxn];
         memset(dis,0,sizeof(dis));     //dis[i] �洢i��v0����̾��롣v0�������һ���ڵ�
         for (i=1;i<=n;i++)
         {
                 for (j=1;j<=es;j++) 
                        if (dis[edge[j][1]]+edge[j][0] < dis[edge[j][2]]) dis[edge[j][2]] = dis[edge[j][1]]+edge[j][0];
         }
         int flag=0;
         for (i=1;i<=es;i++)
         {
                 if (dis[edge[i][1]] + edge[i][0] < dis[edge[i][2]]) {flag=1;break;}
         }
         if (flag) printf("successful conspiracy\n");
         else printf("lamentable kingdom\n");
 }
 int main()
 { 
         int i;
         scanf("%d",&n);
         while (n!=0)
         {
                 scanf("%d",&m);
                 es=0;                          //es��ʾ������ע����0
                 for (i=1;i<=m;i++)
                 {
                         int a,b,c;
                         char ss[5];
                         scanf("%d%d",&a,&b);
                         scanf("%s",ss);
                         scanf("%d",&c);
                         if (ss[0]=='l') add_edge(a-1,a+b,c-1);
                         else add_edge(a+b,a-1,-c-1);
                 }
                 Bellmanford();
                 scanf("%d",&n);
         }
         return 0;
 }
