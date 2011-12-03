//2-SAT,





#include <stdio.h>


#include <memory.h>


#include <algorithm>


#include <vector>


using namespace std;





class Graph
{





public:


    //边的最大规模，顶点最大规模


    enum
    {


        MAX_NUM_EDGE = 1000010, MAX_NUM_NODE = 1010


    };





    //边的定义


    struct Edge
    {


        int to;


        Edge *next;


    } e[2 * MAX_NUM_EDGE];





    //每个顶点邻接边表的表头，表尾（表空则为0），和逆向边表;


    Edge *e_begin[MAX_NUM_NODE], *e_end[MAX_NUM_NODE], *e_reverse[MAX_NUM_NODE];


    //"新图"的邻接边表，"新图"由原图的 强连通分量 组成。（该表剔除重边和自环）


    Edge *e_reduced[MAX_NUM_NODE];


    //每个顶点所属的强连通分量编号（从0开始）


    int flag[MAX_NUM_NODE];





    //初始化图


    void init();


    //插入一条由form指向to的边


    void insertEdge ( int form, int to );





    //求强连通分量


    //n为顶点数量, reduce表示是否生成"新图"的邻接边表，生成新图后原图的边表失效


    //返回强连通分量个数


    int Strongly_Connected_Component ( int n, bool reduce = false );


    int SCC_Num;


    //求出一组可行解，但要先执行强联通分量，并得到e_reduced


    void Result();





private:


    int sign[MAX_NUM_NODE], count;


    int en, n;


    int st[MAX_NUM_NODE], sn;


    bool reduce;


    //简化边表


    void Reduced ( int m );


    //两次DFS


    void DFS ( int k );


    void RDFS ( int k );





};





///////////////////////////////////////////////////////


//函数实现





void Graph::init()
{
    n = en = 0;
    memset ( e_begin, 0, sizeof e_begin );
    memset ( e_reverse, 0, sizeof e_reverse );
    memset ( e_end, 0, sizeof e_end );
}





void Graph::insertEdge ( int from, int to )
{
    //插入边
    e[en].to = to;
    e[en].next = e_begin[from];
    e_begin[from] = &e[en];
    //修改边表结尾
    if ( e_end[from] == 0 )
        e_end[from] = &e[en];
    en++;
    //插入逆向边
    e[en].to = from;
    e[en].next = e_reverse[to];
    e_reverse[to] = &e[en];
    en++;
}





//DFS


void Graph::DFS ( int k )
{
    sign[k] = count;
    for ( Edge *p = e_begin[k]; p; p = p->next )
        if ( sign[p->to] != count )
            DFS ( p->to );
    st[sn++] = k;
}





//DFS2


void Graph::RDFS ( int k )
{
    flag[k] = count;
    //把 顶点k 的边表加入到 强连通分量count 的边表中
    if ( reduce && e_begin[k] )
    {
        e_end[k]->next = e_reduced[count];
        e_reduced[count] = e_begin[k];
    }
    for ( Edge *p = e_reverse[k]; p; p = p->next )
        if ( flag[p->to] == -1 )
            RDFS ( p->to );
}





int Graph::Strongly_Connected_Component ( int n, bool reduce/* = false */ )
{
    int i, m;
    this->n = n;
    this->reduce = reduce;
    //DFS
    memset ( sign, 0, sizeof sign );
    sn = 0;
    count = 1;
    for ( i = 0; i < n; i++ )
        if ( sign[i] < count )
            DFS ( i );
    //DFS again
    count = 0;
    memset ( flag, -1, sizeof sign );
    if ( reduce )
        memset ( e_reduced, 0, sizeof e_reduced ); //初始化新图边表
    while ( sn-- ) //按出栈顺序逆向DFS
    {
        if ( flag[st[sn]] == -1 )
        {
            //新的强连通分量
            RDFS ( st[sn] );
            count++;
        }
    }
    m = count;
    if ( reduce )
        Reduced ( count ); //简化新图边表
    SCC_Num = m;
    return m;
}





void Graph::Reduced ( int m )
{
    int to;
    count = 2;
    for ( int i = 0; i < m; i++ )
    {
        Edge *t = 0;
        for ( Edge * q, *p = e_reduced[i]; p; p = q )
        {
            q = p->next;
            to = flag[p->to];
            //if 不是指向自己 and 不是重边
            if ( to != i && sign[to] < count )
            {
                sign[to] = count;
                p->to = to;
                p->next = t;
                t = p;
            }
        }
        e_reduced[i] = t;
        count++; //count++ 避免清除sign
    }
}





void Graph::Result() //需要对新图拓扑排序，然后从底层向上找


{
    int i;
    int num = SCC_Num;
    vector<int> pto[MAX_NUM_NODE]; //存储指向该点的所有
    int opp[MAX_NUM_NODE]; //存储每个SCC的相对点（即不能同时取的点）
    int indeg[MAX_NUM_NODE];
    memset ( indeg, 0, sizeof ( indeg ) );
    int nodes[MAX_NUM_NODE], np = -1;
    for ( i = 0; i < 4; i++ ) //顶点数，暂时为8,i+4为其相对顶点
    {
        opp[flag[i]] = flag[i + 4];
        opp[flag[i + 4]] = flag[i];
    }
    for ( i = 0; i < num; i++ )
    {
        Edge *p = e_reduced[i];
        while ( p )
        {
            pto[p->to].push_back ( i );
            indeg[p->to]++;
            p = p->next;
        }
    }
    for ( i = 0; i < num; i++ )
    {
        if ( indeg[i] == 0 )
        {
            np++;
            nodes[np] = i;
        }
    }
    int h = 0;
    while ( h <= np )
    {
        int k = nodes[h];
        Edge *p = e_reduced[k];
        while ( p )
        {
            indeg[p->to]--;
            if ( indeg[p->to] == 0 )
            {
                np++;
                nodes[np] = p->to;
            }
            p = p->next;
        }
        h++;
    }
    short color[MAX_NUM_NODE]; //各点着色，1表示选取，2表示不能选
    int d[MAX_NUM_NODE];
    memset ( color, 0, sizeof ( color ) );
    int t;
    int ii;
    for ( ii = np; ii >= 0; ii-- )
    {
        i = nodes[ii];
        if ( color[i] != 0 )
            continue;
        color[i] = 1;
        color[opp[i]] = 2;
        vector<int>::iterator p = pto[opp[i]].begin();
        h = -1;
        for ( ; p != pto[opp[i]].end(); p++ )
        {
            h++;
            d[h] = *p;
        }
        t = h;
        h = 0;
        while ( h <= t )
        {
            color[d[h]] = 2;
            for ( p = pto[d[h]].begin(); p != pto[d[h]].end(); p++ )
            {
                if ( color[*p] != 0 )
                    continue;
                color[*p] = 2;
                t++;
                d[t] = *p;
            }
            h++;
        }
    }
    for ( i = 0; i < num; i++ )
        printf ( "color[%d]==%d\n", i, color[i] );
    for ( i = 0; i < 4; i++ ) //此处节点总数为８
    {
        if ( color[flag[i]] == 1 )
            printf ( "%d ", i );
        else
            printf ( "%d ", i + 4 );
    }
    printf ( "\n" );
}





Graph g;





int main()
{
    g.init();
    g.insertEdge ( 0, 1 );
    g.insertEdge ( 1, 0 );
    g.insertEdge ( 4, 5 );
    g.insertEdge ( 5, 4 );
    g.insertEdge ( 1, 7 );
    g.insertEdge ( 3, 5 );
    int num = g.Strongly_Connected_Component ( 8, true );
    int i;
    printf ( "num = %d\n", num );
    for ( i = 0; i < 8; i++ )
        printf ( "flag[%d] == %d\n", i, g.flag[i] );
    for ( i = 0; i < num; i++ )
    {
        Graph::Edge *p = g.e_reduced[i];
        while ( p )
        {
            printf ( "%d ", p->to );
            p = p->next;
        }
        printf ( "is connected to component %d.\n", i );
    }
    for ( i = 0; i < 4; i++ )
        if ( g.flag[i] == g.flag[i + 4] )
        {
            printf ( "No solution.\n" );
            return 0;
        }
    g.Result();
    return 0;
}




