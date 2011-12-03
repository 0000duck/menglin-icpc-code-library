/*树的同构判定 PKU1635 AC
 */
#include <string.h>
#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;
const int maxn = 3200; //最大顶点数 
struct nodestype                        //节点类型
{
    int lp;                                     //length of ordered label
    vector<int> orderedlabel;              //所有儿子的标号序列
    vector<int> sortedchildren;
    int label;                                  //他的标号
    int parent;                                 //父亲节点，树的表示法
    int level;    
}nodes[maxn];
int n;
class treetype
{
    int i;
    public:        
        int root;
        int height;//根的深度为0
        int size;//节点数
        void build(char s[maxn])                //建树
        {
            n++;
            root=n;
            size=1;
            height=0;
            nodes[root].parent = root;
            nodes[root].level = 0;
            int lev=0;
            int p=root;
            for (i=0;s[i]!='\0';i++)
            {
                if (s[i]=='0') 
                {
                    lev++;
                    n++;
                    nodes[n].level=lev;
                    nodes[n].parent = p;
                    p=n;
                    if (lev > height) height = lev;
                    size++;
                }
                else
                {
                    lev--;
                    p=nodes[p].parent;
                }                
            }
        }
}tree1,tree2;
int L[3][maxn];
int maxer(int a,int b)
{
    if (a>b) return a;
    return b;
}
bool comp(const int &a,const int &b)
{    
    vector<int>::iterator p = nodes[a].orderedlabel.begin();
    vector<int>::iterator q = nodes[b].orderedlabel.begin();
    
    for (;p!=nodes[a].orderedlabel.end() && q!=nodes[b].orderedlabel.end();p++,q++)
    {
        if (*p!=*q) return (*p < *q);
    }
    return nodes[a].orderedlabel.size() < nodes[b].orderedlabel.size();
}
int isomorphic()
{
    if (tree1.height != tree2.height) return 0;
    if (tree1.size != tree2.size) return 0;
    if (tree1.height == tree1.size-1 && tree1.height != tree2.height) return 0;
    if (tree2.height == tree2.size-1 && tree1.height != tree2.height) return 0;    
    int h=maxer(tree1.height,tree2.height);
    memset(L,0,sizeof(L));
    int i,j;
    for (i=1;i<=n;i++)
    {
        int lev = nodes[i].level;
        if (lev != h)  continue;
        L[lev%2][0]++;
        L[lev%2][L[lev%2][0]] = i;
        if (lev == h) nodes[i].lp=1;
    }            
    for (i=h-1;i>=0;i--)
    {
        for (j=1;j<=n;j++)
       {
                int lev = nodes[j].level;
                if (lev != i)  continue;
                L[lev%2][0]++;
                L[lev%2][L[lev%2][0]] = j;
                if (lev == h) nodes[j].lp=1;
        }
        for (j=1;j<=L[(i+1)%2][0];j++)
        {
            int p = nodes[L[(i+1)%2][j]].parent;
            nodes[p].lp++;
            nodes[p].orderedlabel.push_back(nodes[L[(i+1)%2][j]].label);
        }
        for (j=1;j<=L[i%2][0];j++)
            if (nodes[L[i%2][j]].lp==0) {nodes[L[i%2][j]].lp++;nodes[L[i%2][j]].orderedlabel.push_back(0);}
        sort(L[i%2]+1,L[i%2]+L[i%2][0]+1,comp);
        for (j=1;j<=L[i%2][0];j++)
        {
            int *p = lower_bound(L[i%2]+1,L[i%2]+L[i%2][0]+1,L[i%2][j],comp);
            nodes[L[i%2][j]].label = p-L[i%2]-1;
        }
    }
    if (nodes[tree1.root].label == nodes[tree2.root].label) return 1;
    return 0;
}
int main()
{
    int cs;
    freopen("e.in","r",stdin);
    freopen("out","w",stdout);
    scanf("%d",&cs);
    while (cs--)
    {   
        memset(nodes,0,sizeof(nodes));
        n=0;                            //节点数清0，两棵树是连续编号的
        char s[maxn];
        scanf("%s",s);
        tree1.build(s);
        scanf("%s",s);
        tree2.build(s);
        if (isomorphic()) printf("same\n");
        else printf("different\n");
    }    
    return 0;
}
