//FORD_FULKERSON


#include <iostream>


#include <queue>


using namespace std;





//邻接阵实现


const long MAXN = 1000;


const long lmax = 0x7FFFFFFF;





long Net[MAXN][MAXN];//残余网络


long Path[MAXN];//增广路径


long Lv[MAXN];//增广路径通过容量





queue<long> q;


long m, n; //点，边


long Start, End;





void init()


{
    while ( !q.empty() )
    {
        q.pop();
    }
    memset ( Path, -1, sizeof ( Path ) );
}








long Min ( long a, long b )


{
    return a < b ? a : b;
}





long bfs()


{
    init();
    Path[Start] = 0;
    Lv[Start] = lmax;
    q.push ( Start );      //queue q是用来搜索一个一个的图上的顶点的
    while ( !q.empty() )
    {
        long t = q.front();
        q.pop();         //取了队列头，然后给他pop掉 ，
        if ( t == End )
        {
            break;         //因为是先进先出
        }           //搜索到了最后一个点，就不要搜了
        long i;
        for ( i = 1; i <= m; ++i ) //i是点
        {
            if ( i != Start && Path[i] == -1 && Net[t][i] ) //Net[t][i]=1 表示所有从 t~i 残余网络 t->i并且是可达的
            {
                Lv[i] = Min ( Lv[t], Net[t][i] );
                q.push ( i );
                Path[i] = t;     //path[i]是现这条并不是完全的增光的前一个节点
            }
        }
    }
    if ( Path[End] == -1 )    //搜到end这结点了，即从start到end 有一条通路，就是通过这个path来指示的
    {
        return -1;
    }
    return Lv[m];
}





void print ( long n )


{
    printf ( "%ld\n", n );
}





void Ford_Fulkerson()


{
    long i;
    long Max_Flow = 0;
    for ( i = 0; i < n; ++i )   //n表示边数量，m表示点数量
    {
        long from, to, cost;
        scanf ( "%ld %ld %ld", &from, &to, &cost ); //*********************************//无比经典
        Net[from][to] = cost;        //非常经典啊，一个点到另一个点的残余量，肯定是正的，能加上的流量数
        //这两个点总是在互换的，如果x=u->v 为正，表示流是从u->v，反之，则为v->u
        //cost为剩余量           //而，x为负的时候，v->u是假流量，所以我们只取正的情况，真流量。x=u->v为负和v->u为正的重复了，只考虑一次就够了，所以都取正即可，无敌的存在
        //如果在现有网络上扩展 剩余量为容量-已占用量   //另外，残余可增广流量肯定为正的，因为本来取法就是只取正的真流量，所以增广流量为正
        //最大流结果要加上已流入的量
    }
    scanf ( "%ld %ld", &Start, &End );
    long step;
    while ( ( step = bfs() ) != -1 ) //反搜增广路径并调整流量
    {
        Max_Flow += step;
        long now = End;
        while ( now != Start )
        {
            long pre = Path[now];   //path[now]存的now为到达点的该点的前一个起始点
            Net[pre][now] -= step;  //不会到负数去，因为 ‘-’ 总是减min()的，上面的bfs是这样子，所以不会减成负数
            Net[now][pre] += step;  //而这里是在+，加上去，肯定不会负，这里Net[][]并不是 最大的水管容量，而是有多少可以减，残余网络的剩余量，用来减的
            now = pre;
        }
    }
    print ( Max_Flow );
}





int main()


{
    while ( scanf ( "%ld %ld", &m, &n ) != EOF )
    {
        Ford_Fulkerson();
    }
    return 0;
}

