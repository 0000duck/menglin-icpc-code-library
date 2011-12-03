/*Logical Mars Codes Library
 * 
 * 差分约束系统
 *
 *      一般节点S都是都是某个数列的和，用起来很灵活。比如区间问题，节点设为区间点上的数字出现次数
 *      的和，就可以解一些区间限制型的问题。注意输出时，个数应该是dis[n] - dis[0]。
 *      求最大值，就是用<=构图求最短路。
 *      求最小值，就是用>=构图求最长路。
 */
 #include <string.h>
 #include <stdio.h>
 const int maxn = 110;//最大顶点数
 const int maxm = 110;//最大边数
 int s[maxn];
 int edge[maxm][3];
 int es;
 int n,m;
void add_edge(int a,int b,int c) //从a到b加一条边权为c的边
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
         memset(dis,0,sizeof(dis));     //dis[i] 存储i到v0的最短距离。v0是虚设的一个节点
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
                 es=0;                          //es表示边数，注意清0
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
